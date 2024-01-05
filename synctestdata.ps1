# Script that synchronizes the local test data
#
# Version: 20230709

$TestSet = "public"
$TestInputDirectory = "tests/input"
$TestFiles = "DiskDescriptor.xml hfsplus.hdd hfsplus.hdd.0.{5fbaabe3-6958-40ff-92a7-860e329aab41}.hds"

If (-Not (Test-Path ${TestInputDirectory}))
{
	New-Item -Name ${TestInputDirectory} -ItemType "directory" | Out-Null
}
If (-Not (Test-Path "${TestInputDirectory}\${TestSet}"))
{
	New-Item -Name "${TestInputDirectory}\${TestSet}" -ItemType "directory" | Out-Null
}
ForEach ($TestFile in ${TestFiles} -split " ")
{
	New-Item -Name "${TestInputDirectory}\${TestSet}\hfsplus.hdd" -ItemType "directory" | Out-Null

	$Url = "https://github.com/log2timeline/dfvfs/blob/main/test_data/hfsplus.hdd/${TestFile}?raw=true"

	Invoke-WebRequest -Uri ${Url} -OutFile "${TestInputDirectory}\${TestSet}\hfsplus.hdd\${TestFile}"
}

@"
hfsplus.hdd\DiskDescriptor.xml
"@ | Out-File -FilePath files

New-Item -Name "${TestInputDirectory}\.libphdi\${TestSet}" -ItemType "directory" | Out-Null
Copy-Item files -Destination "${TestInputDirectory}\.libphdi\${TestSet}\files"

New-Item -Name "${TestInputDirectory}\.pyphdi\${TestSet}" -ItemType "directory" | Out-Null
Copy-Item files -Destination "${TestInputDirectory}\.pyphdi\${TestSet}\files"

New-Item -Name "${TestInputDirectory}\.phditools\${TestSet}" -ItemType "directory" | Out-Null
Copy-Item files -Destination "${TestInputDirectory}\.phditools\${TestSet}\files"
