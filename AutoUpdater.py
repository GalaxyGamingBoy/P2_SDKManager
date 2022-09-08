import sys, os
from urllib import request
from zipfile import ZipFile

argv = sys.argv
argc = len(argv)

def printUsage():
    print("Usage: python(3) AutoUpdater.py [github_project] [zip_scheme] [executable_name]")

def argumentCheck():
    return argc == 4

def downloadZIP(url, filename):
    request.urlretrieve(url, filename)

def removeOldFiles():
    os.system(f"rm {argv[3]}*")

def extractUpdate(filename, condition):
    with ZipFile(f"{filename}.zip", "r") as zip:
            zipExtractedFilenames = zip.namelist()
            for filename in zipExtractedFilenames:
                if filename.startswith(condition):
                    zip.extract(filename)

def cleanup():
    os.remove("update.zip")

def run():
    if argumentCheck():
        # Download the update ZIP
        print("Starting Download...")
        downloadZIP(f"https://github.com/GalaxyGamingBoy/{argv[1]}/releases/latest/download/{argv[2]}.zip", "update.zip")
        print("Download Complete!")

        # Remove old version
        print("Removing the Old Version...")
        removeOldFiles()
        print("Old Version Removed!")

        # Extract the update ZIP
        print("Extracting && Updating Executable to Latest Version...")
        extractUpdate("update", argv[3])

        # Cleanup
        print("Starting CleanUp...")
        cleanup()
        print("CleanUp Complete!")
        print("\nUpdate Complete!")
    else:
        printUsage()
        exit(1)



if __name__ == "__main__":
    run()