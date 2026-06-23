# Script that synchronizes the local test data

$TestsInputDirectory = "tests\input"
$TestSet = "public"
$TestFiles = "DiskDescriptor.xml hfsplus.hdd hfsplus.hdd.0.{5fbaabe3-6958-40ff-92a7-860e329aab41}.hds"

If (-Not (Test-Path ${TestsInputDirectory}))
{
	New-Item -Name ${TestsInputDirectory} -ItemType "directory" | Out-Null
}
If (-Not (Test-Path "${TestsInputDirectory}\${TestSet}"))
{
	New-Item -Name "${TestsInputDirectory}\${TestSet}" -ItemType "directory" | Out-Null
}
New-Item -Name "${TestsInputDirectory}\${TestSet}\hfsplus.hdd" -ItemType "directory" | Out-Null

ForEach ($TestFile in ${TestFiles} -split " ")
{
	$UrlTestFile = [System.Uri]::EscapeDataString("${TestFile}")
	$Url = "https://raw.githubusercontent.com/log2timeline/dfvfs/refs/heads/main/test_data/hfsplus.hdd/${UrlTestFile}"

	$ProgressPreference = 'SilentlyContinue'
	Invoke-WebRequest -Uri ${Url} -OutFile "${TestsInputDirectory}\${TestSet}\hfsplus.hdd\${TestFile}"
}

@"
hfsplus.hdd\DiskDescriptor.xml
"@ | Out-File -FilePath files

New-Item -Name "${TestsInputDirectory}\.libphdi\${TestSet}" -ItemType "directory" | Out-Null
Copy-Item files -Destination "${TestsInputDirectory}\.libphdi\${TestSet}\files"

New-Item -Name "${TestsInputDirectory}\.pyphdi\${TestSet}" -ItemType "directory" | Out-Null
Copy-Item files -Destination "${TestsInputDirectory}\.pyphdi\${TestSet}\files"

New-Item -Name "${TestsInputDirectory}\.phdiinfo\${TestSet}" -ItemType "directory" | Out-Null
Copy-Item files -Destination "${TestsInputDirectory}\.phdiinfo\${TestSet}\files"
