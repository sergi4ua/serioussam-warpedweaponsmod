<#
.SYNOPSIS
  Installs Warped Weapons (Plasma Thrower + Mine Layer) into Serious Sam Classic:
  The Second Encounter 1.07, replacing the game's entities library.

.DESCRIPTION
  * Backs up the original Bin\EntitiesMP.dll (first install only) to <game>\WarpedWeaponsBackup.
  * Copies the new Bin\EntitiesMP.dll, Classes\EnergyMine.ecl, WarpedWeapons.gro and the
    NETRICSA weapon messages into the game folder.
  * If Serious Sam Classics Patch 1.9.4 is installed, also replaces (and backs up) its
    Bin\Entities_Custom.dll and Bin\Plugins\AdvancedHUD.dll, so the weapons work in
    SeriousSam_Custom.exe too. Other versions of the Classics Patch are left alone.
  * Adds the "Alternate Fire", "Plasma Thrower" and "Mine Layer" buttons to every controls
    file in <game>\Controls (presets and player profiles). Keys that are already taken in
    a file are left unassigned there.
  Run Uninstall.ps1 (or Uninstall.bat) to go back to the original game.

.PARAMETER GameDir
  The game folder. If omitted, the script looks above its own folder, then in the Steam
  libraries, and finally asks.
#>
param([string]$GameDir)

$ErrorActionPreference = 'Stop'
. (Join-Path $PSScriptRoot 'WarpedWeapons.Common.ps1')

$payload = Join-Path $PSScriptRoot 'Files'
if (-not (Test-Path -LiteralPath $payload)) { throw "Missing $payload - extract the whole archive first." }

$GameDir = Find-GameDir $GameDir
Write-Host "Game folder: $GameDir"
Assert-GameNotRunning

# the retail game loads Bin\GameMP.dll / Bin\EntitiesMP.dll because ModEXT.txt says "MP"
$modExtFile = Join-Path $GameDir 'ModEXT.txt'
if (Test-Path -LiteralPath $modExtFile) {
  $modExt = (Get-Content -LiteralPath $modExtFile -Raw).Trim()
  if ($modExt -ne 'MP') {
    throw "$modExtFile contains '$modExt' instead of 'MP', so the game would not load Bin\EntitiesMP.dll. Change it back to MP (or use Steam's 'Verify integrity of game files') and run the installer again."
  }
}

$backupDir = Join-Path $GameDir $BackupDirName
$manifestPath = Join-Path $backupDir $ManifestName
New-Item -ItemType Directory -Force $backupDir | Out-Null

# payloads: the retail game, plus the Classics Patch files when its supported version is installed
$payloads = @($payload)
$cpPayload = Join-Path $PSScriptRoot 'Files_ClassicsPatch'
switch (Get-ClassicsPatchState $GameDir) {
  'supported' { if (Test-Path -LiteralPath $cpPayload) { $payloads += $cpPayload; Write-Host "Serious Sam Classics Patch $ClassicsPatchVersion found: installing for it too." } }
  'other'     { Write-Warning "This Serious Sam Classics Patch version isn't supported (Warped Weapons is built for $ClassicsPatchVersion). The weapons are installed for the retail game (Bin\SeriousSam.exe) only." }
}

# manifest: one game-relative path per line, for every file this mod put into the game folder
$installed = [System.Collections.Generic.List[string]]::new()
if (Test-Path -LiteralPath $manifestPath) { $installed.AddRange([string[]](Get-Content -LiteralPath $manifestPath | Where-Object { $_ })) }

foreach ($dir in $payloads) {
  $files = @(Get-ChildItem -LiteralPath $dir -Recurse -File | ForEach-Object { $_.FullName.Substring($dir.Length + 1) })

  # 1. back up the original files that get replaced
  foreach ($rel in $files | Where-Object { $ReplacedFiles -contains $_ }) {
    $src = Join-Path $GameDir $rel
    $bak = Join-Path $backupDir $rel
    if (Test-Path -LiteralPath $bak) { continue }                 # reinstall/update: keep the first backup
    if (-not (Test-Path -LiteralPath $src)) { continue }
    if (Test-ModBuild $src $rel) {
      Write-Warning "$rel is already a Warped Weapons build and there is no backup of the original. Uninstalling will not be able to restore it; use Steam's 'Verify integrity of game files' (or reinstall the Classics Patch) instead."
      continue
    }
    New-Item -ItemType Directory -Force (Split-Path $bak) | Out-Null
    Copy-Item -LiteralPath $src $bak
    Write-Host "  backed up $rel"
  }

  # 2. copy the mod files
  foreach ($rel in $files) {
    $dst = Join-Path $GameDir $rel
    New-Item -ItemType Directory -Force (Split-Path $dst) | Out-Null
    Copy-Item -LiteralPath (Join-Path $dir $rel) $dst -Force
    if (-not $installed.Contains($rel)) { $installed.Add($rel) }
    Write-Host "  installed $rel"
  }
}
Set-Content -LiteralPath $manifestPath -Value $installed -Encoding ASCII

# 3. controls
foreach ($ctl in Get-ControlsFiles $GameDir) {
  $bak = Join-Path $backupDir "Controls\$($ctl.Name)"
  if (-not (Test-Path -LiteralPath $bak)) {
    New-Item -ItemType Directory -Force (Split-Path $bak) | Out-Null
    Copy-Item -LiteralPath $ctl.FullName $bak
  }
  Add-WarpedButtons $ctl.FullName
  Write-Host "  added buttons to Controls\$($ctl.Name)"
}

Write-Host ''
Write-Host 'Warped Weapons is installed. Start the game as usual.'
Write-Host 'Plasma Thrower: 9, Mine Layer: -, Alternate Fire: G, Right Ctrl or the sniper scope key'
Write-Host '(change them in Options > Players and Controls > Change controls > Customize buttons).'
