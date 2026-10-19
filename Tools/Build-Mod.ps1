<#
.SYNOPSIS
  Builds Warped Weapons for Serious Sam: The Second Encounter 1.07, assembles the release,
  and optionally installs it and/or packs the ZIP archives.

.DESCRIPTION
  1. Builds WarpedWeapons.sln with MSBuild (Visual Studio 2026, Win32): the retail entities
     (Sources\EntitiesMP) and, for Serious Sam Classics Patch 1.9.4, its entities
     (Sources\ClassicsPatch\EntitiesTSE) and Advanced HUD plugin (Sources\ClassicsPatch\AdvancedHUD).
  2. Packs the Plasmathrower/Minelayer assets from the Seriously Warped Deathmatch archive
     (Mods\Warped\Warped3.gro) into WarpedWeapons.gro.
  3. Assembles the release in Build\Replacement\WarpedWeapons-<version>: the installer
     scripts (Installer\) plus Files\ and Files_ClassicsPatch\, laid out like the game folder:
       Files\Bin\EntitiesMP.dll                  (the entities DLL, replaces the retail one)
       Files\Classes\EnergyMine.ecl
       Files\WarpedWeapons.gro
       Files\Data\Messages\Weapons\*.txt
       Files_ClassicsPatch\Bin\Entities_Custom.dll        (only installed with Classics Patch 1.9.4)
       Files_ClassicsPatch\Bin\Plugins\AdvancedHUD.dll
     With -Layout ModFolder it assembles Build\Mod\WarpedWeapons instead: a separate mod
     folder (+game WarpedWeapons) that leaves the game's own files alone.
  4. -Install runs the release's Install.ps1 on <GameDir> (or copies the mod folder into
     <GameDir>\Mods with -Layout ModFolder).
  5. -Package writes Build\Packages\WarpedWeapons-<version>.zip (the release) and
     WarpedWeapons-<version>-src.zip (the source code).

.PARAMETER GameDir
  Root of the Serious Sam: The Second Encounter installation (defaults to the parent of
  this repository).

.PARAMETER Configuration
  Release (default) or Debug.

.PARAMETER Layout
  Replacement (default) or ModFolder.

.PARAMETER Install
  Install the assembled release into <GameDir>.

.PARAMETER Package
  Create the ZIP archives in Build\Packages.

.PARAMETER SkipBuild
  Do not run MSBuild; use the last build output.
#>
param(
  [string]$GameDir,
  [ValidateSet('Release','Debug')][string]$Configuration = 'Release',
  [ValidateSet('Replacement','ModFolder')][string]$Layout = 'Replacement',
  [switch]$Install,
  [switch]$Package,
  [switch]$SkipBuild
)

$ErrorActionPreference = 'Stop'
$repo = Split-Path -Parent $PSScriptRoot
if (-not $GameDir) { $GameDir = Split-Path -Parent $repo }
$GameDir = (Resolve-Path $GameDir).Path

$version = '1.2.0'
$modName = 'WarpedWeapons'
$modExt  = 'WW'

function Find-MSBuild {
  $vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
  if (Test-Path $vswhere) {
    $path = & $vswhere -latest -products * -requires Microsoft.Component.MSBuild -find 'MSBuild\**\Bin\MSBuild.exe' | Select-Object -First 1
    if ($path) { return $path }
  }
  $cmd = Get-Command msbuild.exe -ErrorAction SilentlyContinue
  if ($cmd) { return $cmd.Source }
  throw 'MSBuild.exe not found. Install Visual Studio 2026 with the "Desktop development with C++" workload (MSVC x86 tools).'
}

# Replaces one ASCII string with another one of the same length; fails unless it occurs exactly once.
function Copy-WithStringSwap([string]$src, [string]$dst, [string]$from, [string]$to) {
  if ($from.Length -ne $to.Length) { throw "String swap must keep the length ($from -> $to)" }
  $bytes = [IO.File]::ReadAllBytes($src)
  $text  = [Text.Encoding]::GetEncoding(28591).GetString($bytes)   # 1:1 byte <-> char mapping
  $hits  = [regex]::Matches($text, [regex]::Escape($from))
  if ($hits.Count -ne 1) { throw "Expected exactly one '$from' in $src, found $($hits.Count)" }
  $patch = [Text.Encoding]::ASCII.GetBytes($to)
  [Array]::Copy($patch, 0, $bytes, $hits[0].Index, $patch.Length)
  [IO.File]::WriteAllBytes($dst, $bytes)
}

function New-CleanDir([string]$path) {
  if (Test-Path $path) { Remove-Item $path -Recurse -Force }
  New-Item -ItemType Directory -Force $path | Out-Null
}

Add-Type -AssemblyName System.IO.Compression, System.IO.Compression.FileSystem

# Zips $files (absolute paths under $root) into $zipPath, stored under $prefix\<relative path>.
function New-Zip([string]$zipPath, [string]$root, $files, [string]$prefix) {
  if (Test-Path $zipPath) { Remove-Item $zipPath -Force }
  $zip = [IO.Compression.ZipFile]::Open($zipPath, [IO.Compression.ZipArchiveMode]::Create)
  try {
    foreach ($f in $files) {
      $rel = $f.Substring($root.Length + 1)
      $name = (Join-Path $prefix $rel).Replace('\', '/')
      [IO.Compression.ZipFileExtensions]::CreateEntryFromFile($zip, $f, $name, [IO.Compression.CompressionLevel]::Optimal) | Out-Null
    }
  } finally { $zip.Dispose() }
  Write-Host "Wrote $zipPath ($([math]::Round((Get-Item $zipPath).Length / 1MB, 1)) MB, $(@($files).Count) files)"
}

# --- 1. build ---------------------------------------------------------------------------
if (-not $SkipBuild) {
  if (-not (Test-Path (Join-Path $repo 'ThirdParty\ClassicsPatch\Core\Core.h'))) {
    throw 'Serious Sam Classics Patch 1.9.4 sources are missing - run Tools\Get-ClassicsPatch.ps1 first.'
  }
  $msbuild = Find-MSBuild
  Write-Host "Building WarpedWeapons.sln ($Configuration) with $msbuild"
  & $msbuild (Join-Path $repo 'WarpedWeapons.sln') /p:Configuration=$Configuration /p:Platform=Win32 /m /nologo /v:minimal
  if ($LASTEXITCODE -ne 0) { throw "MSBuild failed with exit code $LASTEXITCODE" }
}
$entitiesDll = Join-Path $repo "Build\$Configuration\Entities$modExt.dll"
if (-not (Test-Path $entitiesDll)) { throw "Missing $entitiesDll - build the solution first." }

# --- 2. assets from Seriously Warped Deathmatch ----------------------------------------
$warpedGro = Join-Path $GameDir 'Mods\Warped\Warped3.gro'
if (-not (Test-Path $warpedGro)) { throw "Seriously Warped Deathmatch archive not found: $warpedGro" }
$assetList = Get-Content (Join-Path $repo 'Mod\WarpedAssets.txt') | Where-Object { $_ -and -not $_.StartsWith('#') } | ForEach-Object { $_.Trim().Replace('\','/') }

$assetsDir = Join-Path $repo 'Build\Assets'
New-Item -ItemType Directory -Force $assetsDir | Out-Null
$gro = Join-Path $assetsDir "$modName.gro"
if (Test-Path $gro) { Remove-Item $gro -Force }
$src = [IO.Compression.ZipFile]::OpenRead($warpedGro)
$dst = [IO.Compression.ZipFile]::Open($gro, [IO.Compression.ZipArchiveMode]::Create)
try {
  foreach ($name in $assetList) {
    $entry = $src.Entries | Where-Object { $_.FullName -ieq $name } | Select-Object -First 1
    if (-not $entry) { throw "Asset '$name' not found in $warpedGro" }
    $out = $dst.CreateEntry($entry.FullName, [IO.Compression.CompressionLevel]::Optimal)
    $ins = $entry.Open(); $outs = $out.Open()
    try { $ins.CopyTo($outs) } finally { $outs.Dispose(); $ins.Dispose() }
  }
} finally { $dst.Dispose(); $src.Dispose() }
Write-Host "Packed $($assetList.Count) assets into $gro"

$modTemplate = Join-Path $repo "Mod\$modName"

if ($Layout -eq 'Replacement') {
  # --- 3. release that replaces the game's entities --------------------------------------
  $releaseName = "$modName-$version"
  $stage = Join-Path $repo "Build\Replacement\$releaseName"
  New-CleanDir $stage
  Copy-Item (Join-Path $repo 'Installer\*') $stage -Recurse -Force
  $files = Join-Path $stage 'Files'
  foreach ($d in 'Bin', 'Classes', 'Data\Messages\Weapons') { New-Item -ItemType Directory -Force (Join-Path $files $d) | Out-Null }
  Copy-Item $entitiesDll (Join-Path $files 'Bin\EntitiesMP.dll')
  Copy-Item (Join-Path $modTemplate 'Classes\*.ecl') (Join-Path $files 'Classes')
  Copy-Item (Join-Path $modTemplate 'Data\Messages\Weapons\*.txt') (Join-Path $files 'Data\Messages\Weapons')
  Copy-Item $gro $files
  # Serious Sam Classics Patch 1.9.4: its entities and Advanced HUD plugin with the weapons added
  # (Install.ps1 only installs these when that exact patch version is present)
  $cpFiles = Join-Path $stage 'Files_ClassicsPatch'
  New-Item -ItemType Directory -Force (Join-Path $cpFiles 'Bin\Plugins') | Out-Null
  Copy-Item (Join-Path $repo "Build\$Configuration\ClassicsPatch\Entities_Custom.dll") (Join-Path $cpFiles 'Bin')
  Copy-Item (Join-Path $repo "Build\$Configuration\ClassicsPatch\Plugins\AdvancedHUD.dll") (Join-Path $cpFiles 'Bin\Plugins')
  Write-Host "Release assembled in $stage"

  if ($Install) {
    & (Join-Path $stage 'Install.ps1') -GameDir $GameDir
  }

  if ($Package) {
    # --- 5. archives ------------------------------------------------------------------------
    $packages = Join-Path $repo 'Build\Packages'
    New-Item -ItemType Directory -Force $packages | Out-Null
    New-Zip (Join-Path $packages "$releaseName.zip") $stage @(Get-ChildItem $stage -Recurse -File | ForEach-Object FullName) $releaseName

    # source code: everything except build output and the files Ecc generates from .es;
    # from the SE1 Mod SDK only the parts the build uses
    $generated = @{}
    Get-ChildItem (Join-Path $repo 'Sources') -Recurse -Filter '*.es' | ForEach-Object {
      $base = Join-Path $_.DirectoryName $_.BaseName
      foreach ($g in "$base.cpp", "$base.h", "$($base)_tables.h") { $generated[$g.ToLowerInvariant()] = $true }
    }
    $sdk = Join-Path $repo 'ThirdParty\SE1-ModSDK'
    $sdkParts = @('LICENSE', 'README.md', 'Sources\Includes\LICENSE', 'Sources\Includes\README.md', 'Sources\Includes\Ecc.exe',
                  'Sources\Includes\Engine107', 'Sources\Includes\Common', 'Sources\Includes\CommonModels',
                  'Sources\Includes\Properties')
    $srcFiles = @()
    foreach ($item in 'README.md', 'COPYING', 'WarpedWeapons.sln', 'Installer', 'Mod', 'Sources', 'Tests', 'Tools') {
      $p = Join-Path $repo $item
      if (Test-Path $p -PathType Leaf) { $srcFiles += $p }
      elseif (Test-Path $p) { $srcFiles += Get-ChildItem $p -Recurse -File | ForEach-Object FullName }
    }
    foreach ($item in $sdkParts) {
      $p = Join-Path $sdk $item
      if (Test-Path $p -PathType Leaf) { $srcFiles += $p }
      elseif (Test-Path $p) { $srcFiles += Get-ChildItem $p -Recurse -File | ForEach-Object FullName }
    }
    # Serious Sam Classics Patch sources are not included (its headers pull in the Steamworks
    # SDK); Tools\Get-ClassicsPatch.ps1 fetches them
    $srcFiles = $srcFiles | Where-Object { -not $generated[$_.ToLowerInvariant()] -and $_ -notmatch '\\(\.vs|x64|Debug|Release)\\' -and $_ -notmatch '\.(user|suo|aps)$' }
    New-Zip (Join-Path $packages "$releaseName-src.zip") $repo $srcFiles "$releaseName-src"
  }
}
else {
  # --- 3. separate mod folder (+game WarpedWeapons) ------------------------------------
  # GameWW.dll and GameGUIWW.dll are the retail GameMP.dll/GameGUIMP.dll with their
  # hard-coded library names re-pointed (EntitiesMP.dll -> EntitiesWW.dll,
  # Bin\GameMP.dll -> Bin\GameWW.dll); same-length string swaps, nothing else changes.
  $stage = Join-Path $repo "Build\Mod"
  New-CleanDir $stage
  $modStage = Join-Path $stage $modName
  New-Item -ItemType Directory -Force (Join-Path $modStage 'Bin') | Out-Null

  # static mod files (classes, controls, scripts, messages, ...)
  Copy-Item (Join-Path $modTemplate '*') $modStage -Recurse -Force
  Copy-Item (Join-Path $repo "Mod\$modName.des") $stage -Force
  if (Test-Path (Join-Path $repo "Mod\$($modName)Tbn.tex")) { Copy-Item (Join-Path $repo "Mod\$($modName)Tbn.tex") $stage -Force }
  # per-player controls start from the default preset, so the new buttons (Alternate Fire,
  # Plasma Thrower, Mine Layer) are bound out of the box; otherwise the game would pick up the
  # base game's Controls\ControlsN.ctl, which don't know these buttons
  foreach ($i in 0..7) { Copy-Item (Join-Path $modStage 'Controls\00-Default.ctl') (Join-Path $modStage "Controls\Controls$i.ctl") -Force }
  # saves, demos and levels made with the mod's entities stay in the mod folder (BaseWriteExclude.lst);
  # the game does not create these folders itself
  $writeDirs = @('Demos', 'Levels', 'Scripts', 'SaveGame\Network\Quick', 'SaveGame\SplitScreen\Quick') + (0..7 | ForEach-Object { "SaveGame\Player$_\Quick" })
  foreach ($d in $writeDirs) { New-Item -ItemType Directory -Force (Join-Path $modStage $d) | Out-Null }

  Copy-Item $entitiesDll (Join-Path $modStage 'Bin') -Force
  Copy-WithStringSwap (Join-Path $GameDir 'Bin\GameMP.dll')    (Join-Path $modStage "Bin\Game$modExt.dll")    'EntitiesMP.dll' "Entities$modExt.dll"
  Copy-WithStringSwap (Join-Path $GameDir 'Bin\GameGUIMP.dll') (Join-Path $modStage "Bin\GameGUI$modExt.dll") 'Bin\GameMP.dll' "Bin\Game$modExt.dll"
  Copy-Item $gro $modStage
  Write-Host "Mod folder assembled in $stage"

  if ($Install) {
    $target = Join-Path $GameDir "Mods\$modName"
    Write-Host "Installing into $target"
    New-Item -ItemType Directory -Force $target | Out-Null
    # refresh everything we ship, but keep the player's own controls (Controls\ControlsN.ctl)
    foreach ($d in $writeDirs) { New-Item -ItemType Directory -Force (Join-Path $target $d) | Out-Null }
    Get-ChildItem $modStage -Recurse -File | ForEach-Object {
      $rel = $_.FullName.Substring($modStage.Length + 1)
      $dest = Join-Path $target $rel
      if ($rel -match '^Controls\\Controls\d\.ctl$' -and (Test-Path $dest)) { return }
      New-Item -ItemType Directory -Force (Split-Path $dest) | Out-Null
      Copy-Item $_.FullName $dest -Force
    }
    Copy-Item (Join-Path $stage "$modName.des") (Join-Path $GameDir 'Mods') -Force
    if (Test-Path (Join-Path $stage "$($modName)Tbn.tex")) { Copy-Item (Join-Path $stage "$($modName)Tbn.tex") (Join-Path $GameDir 'Mods') -Force }
  }
  if ($Package) { Write-Warning '-Package is only supported for -Layout Replacement.' }
}
Write-Host 'Done.'
