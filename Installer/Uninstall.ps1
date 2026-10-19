<#
.SYNOPSIS
  Removes Warped Weapons from Serious Sam Classic: The Second Encounter and restores the
  original game files.

.DESCRIPTION
  * Restores the original Bin\EntitiesMP.dll from <game>\WarpedWeaponsBackup.
  * Deletes the files the mod added (listed in WarpedWeaponsBackup\Installed.txt).
  * Removes the "Alternate Fire", "Plasma Thrower" and "Mine Layer" buttons from the
    controls files; all other bindings, including ones changed after installing, stay.
  * Deletes the backup folder.

.PARAMETER GameDir
  The game folder. If omitted, the script looks above its own folder, then in the Steam
  libraries, and finally asks.
#>
param([string]$GameDir)

$ErrorActionPreference = 'Stop'
. (Join-Path $PSScriptRoot 'WarpedWeapons.Common.ps1')

$GameDir = Find-GameDir $GameDir
Write-Host "Game folder: $GameDir"
Assert-GameNotRunning

$backupDir = Join-Path $GameDir $BackupDirName
$manifestPath = Join-Path $backupDir $ManifestName
if (-not (Test-Path -LiteralPath $manifestPath)) { throw "Warped Weapons is not installed in $GameDir (no $BackupDirName\$ManifestName)." }

foreach ($rel in Get-Content -LiteralPath $manifestPath | Where-Object { $_ }) {
  $dst = Join-Path $GameDir $rel
  $bak = Join-Path $backupDir $rel
  if ($ReplacedFiles -contains $rel) {
    # restore the original only while our build is still in place: if Steam or a Classics Patch
    # update has replaced the file since, that newer file stays
    if (Test-ModBuild $dst $rel) {
      if (Test-Path -LiteralPath $bak) {
        Copy-Item -LiteralPath $bak $dst -Force
        Write-Host "  restored $rel"
      } else {
        Write-Warning "No backup of the original $rel; use Steam's 'Verify integrity of game files' (or reinstall the Classics Patch) to restore it."
      }
    } else {
      Write-Host "  kept $rel (no longer the Warped Weapons build)"
    }
  } elseif (Test-Path -LiteralPath $dst) {
    Remove-Item -LiteralPath $dst -Force
    Write-Host "  removed $rel"
    # remove folders the mod created (e.g. Data\Messages\Weapons) once they are empty
    $dir = Split-Path $dst
    while ($dir.Length -gt $GameDir.Length -and -not (Get-ChildItem -LiteralPath $dir -Force | Select-Object -First 1)) {
      Remove-Item -LiteralPath $dir -Force
      $dir = Split-Path $dir
    }
  }
}

foreach ($ctl in Get-ControlsFiles $GameDir) {
  if ((Remove-WarpedButtons $ctl.FullName) -gt 0) { Write-Host "  removed buttons from Controls\$($ctl.Name)" }
}

Remove-Item -LiteralPath $backupDir -Recurse -Force
Write-Host ''
Write-Host 'Warped Weapons has been removed; the game is back to its original files.'
