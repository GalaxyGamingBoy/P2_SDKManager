import sys, os
from urllib import request
from zipfile import ZipFile
from tkinter import messagebox
argv = sys.argv
argc = len(argv)

argc = 4
argv = ["AutoUpdater.py", "P2_SDKManager", "release_p2-sdk-manager_win64", "p2_sdk_manager"]

if sys.platform.startswith("win32") or sys.platform.startswith("cygwin"):
    argv[2] = "release_p2-sdk-manager_win64"
elif sys.platform.startswith("linux"):
    if "arch" in os.uname().release:
        argv[2] = "release_p2-sdk-manager_gnulinux.arch-compile"
    else:
        argv[2] = "release_p2-sdk-manager_gnulinux.debian-compile"
else:
    print("OS Not Supported")
    exit(2)

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
        messagebox.showinfo(title="Update Started!", message="The Update has just started!")

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
        messagebox.showinfo(title="Update Complete!", message="Update is Completed! Run the App to View Changes!")
        print("\nUpdate Complete!")
    else:
        printUsage()
        exit(1)



if __name__ == "__main__":
    if input("Start Update? n/Y: ") == "Y":
        # run()
        downloadZIP(f"https://github.com/GalaxyGamingBoy/{argv[1]}/releases/latest/download/{argv[2]}.zip", "update.zip")
    else:
        print("Update Canceled")
