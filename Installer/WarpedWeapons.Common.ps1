# Shared helpers for Install.ps1 / Uninstall.ps1 (Warped Weapons for Serious Sam: The Second Encounter 1.07).

$BackupDirName = 'WarpedWeaponsBackup'      # <game>\WarpedWeaponsBackup: original files + install manifest
$ManifestName  = 'Installed.txt'

# Original files that the installer overwrites; they are backed up before the first install.
$ReplacedFiles = @('Bin\EntitiesMP.dll', 'Bin\Entities_Custom.dll', 'Bin\Plugins\AdvancedHUD.dll')

# Serious Sam Classics Patch support (Files_ClassicsPatch: Bin\Entities_Custom.dll, Bin\Plugins\AdvancedHUD.dll).
# These are built against one exact release of the patch, recognized by its Bin\ClassicsCore.dll.
$ClassicsPatchVersion = '1.9.4'
$ClassicsCoreSha256   = '1F13A561CC5CCC24A4CE9608674A5F6E52D92B41B3A7B28DA334F986400683CC'

# Text that only occurs in the Warped Weapons builds of the replaced files.
$ModMarkers = @{ 'Bin\EntitiesMP.dll' = 'CEnergyMine'; 'Bin\Entities_Custom.dll' = 'CEnergyMine'; 'Bin\Plugins\AdvancedHUD.dll' = 'AmPlasma.tex' }

# Is the file at $path (game-relative $rel) the Warped Weapons build?
function Test-ModBuild([string]$path, [string]$rel) {
  if (-not (Test-Path -LiteralPath $path)) { return $false }
  return $Latin1.GetString([IO.File]::ReadAllBytes($path)).Contains($ModMarkers[$rel])
}

# 'none', 'supported' or 'other' (a different version of the Classics Patch)
function Get-ClassicsPatchState([string]$gameDir) {
  $core = Join-Path $gameDir 'Bin\ClassicsCore.dll'
  if (-not (Test-Path -LiteralPath $core)) { return 'none' }
  if ((Get-FileHash -LiteralPath $core -Algorithm SHA256).Hash -eq $ClassicsCoreSha256) { return 'supported' }
  return 'other'
}

# Buttons added to every controls file (presets and player profiles).
# A key that is already used by another button in that file is left unassigned ("None").
$WarpedButtons = @(
  @{ Name = 'TTRS Alternate Fire'; Key1 = 'G'; Key2 = 'Right Control'; Var = 'ctl_bSecondaryFire';     After = 'TTRS Fire' },
  @{ Name = 'TTRS Plasma Thrower'; Key1 = '9'; Key2 = 'None';          Var = 'ctl_bSelectWeapon[9]';  After = 'TTRS Cannon' },
  @{ Name = 'TTRS Mine Layer';     Key1 = '-'; Key2 = 'None';          Var = 'ctl_bSelectWeapon[10]'; After = 'TTRS Plasma Thrower' }
)
# button names used by earlier builds (removed / replaced on install)
$ObsoleteButtonNames = @('TTRS Secondary Fire')

$GameProcesses = @('SeriousSam', 'SeriousSamGamespy', 'SeriousSam_Custom', 'DedicatedServer', 'DedicatedServerGamespy',
                   'DedicatedServer_Custom', 'SeriousEditor', 'SeriousEditor32', 'SeriousEditor_Custom')

$Latin1 = [Text.Encoding]::GetEncoding(28591)   # byte-preserving text I/O

function Test-GameDir([string]$dir) {
  if (-not $dir) { return $false }
  return (Test-Path -LiteralPath (Join-Path $dir 'Bin\SeriousSam.exe')) -and
         (Test-Path -LiteralPath (Join-Path $dir 'Bin\GameMP.dll')) -and
         (Test-Path -LiteralPath (Join-Path $dir 'Bin\EntitiesMP.dll'))
}

function Get-SteamLibraries {
  $roots = @()
  foreach ($key in 'HKCU:\Software\Valve\Steam', 'HKLM:\SOFTWARE\WOW6432Node\Valve\Steam', 'HKLM:\SOFTWARE\Valve\Steam') {
    $p = Get-ItemProperty -Path $key -ErrorAction SilentlyContinue
    if ($p.SteamPath)   { $roots += $p.SteamPath }
    if ($p.InstallPath) { $roots += $p.InstallPath }
  }
  $libs = @()
  foreach ($root in ($roots | Select-Object -Unique)) {
    $libs += $root
    $vdf = Join-Path $root 'steamapps\libraryfolders.vdf'
    if (Test-Path -LiteralPath $vdf) {
      foreach ($m in [regex]::Matches((Get-Content -LiteralPath $vdf -Raw), '"path"\s+"([^"]+)"')) {
        $libs += $m.Groups[1].Value -replace '\\\\', '\'
      }
    }
  }
  return $libs | Select-Object -Unique
}

# Finds the game folder: -GameDir, then the folders above this script, then Steam libraries,
# and finally asks the user.
function Find-GameDir([string]$hint) {
  if ($hint) {
    if (Test-GameDir $hint) { return (Resolve-Path -LiteralPath $hint).Path }
    throw "'$hint' is not a Serious Sam: The Second Encounter folder (Bin\SeriousSam.exe, Bin\GameMP.dll and Bin\EntitiesMP.dll are expected)."
  }
  $dir = $PSScriptRoot
  while ($dir) {
    if (Test-GameDir $dir) { return $dir }
    $dir = Split-Path -Parent $dir
  }
  foreach ($lib in Get-SteamLibraries) {
    $candidate = Join-Path $lib 'steamapps\common\Serious Sam Classic The Second Encounter'
    if (Test-GameDir $candidate) { return $candidate }
  }
  Add-Type -AssemblyName System.Windows.Forms
  $dlg = New-Object System.Windows.Forms.FolderBrowserDialog
  $dlg.Description = 'Select the Serious Sam Classic: The Second Encounter folder (the one that contains Bin\SeriousSam.exe)'
  if ($dlg.ShowDialog() -eq [System.Windows.Forms.DialogResult]::OK -and (Test-GameDir $dlg.SelectedPath)) { return $dlg.SelectedPath }
  throw 'Serious Sam: The Second Encounter was not found. Run the script again with -GameDir "<game folder>".'
}

function Assert-GameNotRunning {
  $running = Get-Process -Name $GameProcesses -ErrorAction SilentlyContinue
  if ($running) {
    throw "Close the game first: $(($running | ForEach-Object { $_.ProcessName } | Select-Object -Unique) -join ', ') is running."
  }
}

# --- controls files ----------------------------------------------------------------------
# A .ctl file is a list of "Button" blocks (indented lines follow), then "Axis ..." and
# "Global..." lines. Lines are kept as they are (LF or CRLF) except for the blocks we touch.

function Read-Lines([string]$path) { return ,([System.Collections.Generic.List[string]]($Latin1.GetString([IO.File]::ReadAllBytes($path)) -split "`n")) }
function Write-Lines([string]$path, $lines) { [IO.File]::WriteAllBytes($path, $Latin1.GetBytes(($lines -join "`n"))) }

# returns @{ Name; Start; End } for every Button block (End = index after its last indented line)
function Get-ButtonBlocks($lines) {
  $blocks = @()
  for ($i = 0; $i -lt $lines.Count; $i++) {
    if ($lines[$i].TrimEnd("`r") -ne 'Button') { continue }
    $name = $null; $j = $i + 1
    while ($j -lt $lines.Count -and $lines[$j].StartsWith(' ')) {
      if ($lines[$j] -match '^\s*Name:\s*(.*?)\s*$') { $name = $Matches[1] }
      $j++
    }
    $blocks += @{ Name = $name; Start = $i; End = $j }
  }
  return $blocks
}

function Remove-WarpedButtons([string]$path) {
  $names = @($WarpedButtons | ForEach-Object { $_.Name }) + $ObsoleteButtonNames
  $lines = Read-Lines $path
  $blocks = @(Get-ButtonBlocks $lines | Where-Object { $names -contains $_.Name } | Sort-Object { $_.Start } -Descending)
  foreach ($b in $blocks) {
    $end = $b.End
    if ($end -lt $lines.Count -and $lines[$end].Trim() -eq '') { $end++ }   # the blank separator line
    $lines.RemoveRange($b.Start, $end - $b.Start)
  }
  if ($blocks.Count) { Write-Lines $path $lines }
  return $blocks.Count
}

function Add-WarpedButtons([string]$path) {
  Remove-WarpedButtons $path | Out-Null            # makes reinstalling idempotent
  $lines = Read-Lines $path
  $usedKeys = @{}
  foreach ($l in $lines) { if ($l -match '^\s*Key[12]:\s*(.*?)\s*$' -and $Matches[1] -ne 'None') { $usedKeys[$Matches[1]] = $true } }
  $blankSeparators = ($lines | Where-Object { $_.Trim() -eq '' }).Count -gt 0

  foreach ($btn in $WarpedButtons) {
    $k1 = if ($usedKeys[$btn.Key1]) { 'None' } else { $btn.Key1 }
    $k2 = if ($btn.Key2 -ne 'None' -and $usedKeys[$btn.Key2]) { 'None' } else { $btn.Key2 }
    if ($k1 -eq 'None' -and $k2 -ne 'None') { $k1 = $k2; $k2 = 'None' }
    foreach ($k in $k1, $k2) { if ($k -ne 'None') { $usedKeys[$k] = $true } }
    $block = @('Button', " Name: $($btn.Name)", " Key1: $k1", " Key2: $k2",
               " Pressed:  $($btn.Var) = 1;", " Released: $($btn.Var) = 0;")
    if ($blankSeparators) { $block += '' }

    $blocks = @(Get-ButtonBlocks $lines)
    $anchor = $blocks | Where-Object { $_.Name -eq $btn.After } | Select-Object -First 1
    if ($anchor) {
      $at = $anchor.End
      if ($blankSeparators -and $at -lt $lines.Count -and $lines[$at].Trim() -eq '') { $at++ }
    } elseif ($blocks.Count) {
      $at = $blocks[-1].End
      if ($blankSeparators -and $at -lt $lines.Count -and $lines[$at].Trim() -eq '') { $at++ }
    } else {
      $at = 0
    }
    $lines.InsertRange($at, [string[]]$block)
  }
  Write-Lines $path $lines
}

function Get-ControlsFiles([string]$gameDir) {
  $dir = Join-Path $gameDir 'Controls'
  if (-not (Test-Path -LiteralPath $dir)) { return @() }
  return @(Get-ChildItem -LiteralPath $dir -Filter '*.ctl' -File)   # presets and Controls0..7.ctl, not System\
}
