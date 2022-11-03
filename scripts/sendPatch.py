from ftplib import FTP
import os
import sys

titleIdLookup = {
    "US": '0100000000010000'
}

def listdirs(connection,_path):

    file_list, dirs, nondirs = [], [], []
    try:
        connection.cwd(_path)
    except:
        return []

    connection.retrlines('LIST', lambda x: file_list.append(x.split()))
    for info in file_list:
        ls_type, name = info[0], info[-1]
        if ls_type.startswith('d'):
            dirs.append(name)
        else:
            nondirs.append(name)
    return dirs


def ensuredirectory(connection,root,path):
    return
    print(f"Ensuring {os.path.join(root, path)} exists...")
    if path not in listdirs(connection, root):
        connection.mkd(f'{root}/{path}')


consoleIP = sys.argv[1]
if '.' not in consoleIP:
    print(sys.argv[0], "ERROR: Please specify with `IP=[Your console's IP]`")
    sys.exit(-1)

isNeedOtherSwitch = True

altSwitchIP = sys.argv[2]
if '.' not in altSwitchIP:
    isNeedOtherSwitch = False

consolePort = 5000

if len(sys.argv) < 4:
    projName = 'StarlightBase'
else:
    projName = sys.argv[3]

curDir = os.curdir

ftp = FTP()

otherftp = FTP()

print(f'Connecting to {consoleIP}... ', end='')
ftp.connect(consoleIP, consolePort)
print('logging into server...', end='')
ftp.login('amethyst','password')
print('Connected!')

if isNeedOtherSwitch:
    print(f'Connecting to {altSwitchIP}... ', end='')
    otherftp.connect(altSwitchIP, consolePort)
    print('logging into server...', end='')
    otherftp.login('crafty','boss')
    print('Connected!')

patchDirectories = []

root, dirs, _ = next(os.walk(curDir))

for dir in dirs:
    if dir.startswith("starlight_patch_"):
        patchDirectories.append((os.path.join(root, f'{dir}/atmosphere/exefs_patches/{projName}'), projName))

# ensuredirectory(ftp, '', 'atmosphere')
# ensuredirectory(ftp, '/atmosphere', 'exefs_patches')

for patchDir in patchDirectories:
    dirPath = patchDir[0]
    dirName = patchDir[1]
    ensuredirectory(ftp, '/atmosphere/exefs_patches', patchDir[1])
    _, _, files = next(os.walk(dirPath))
    for file in files:
        fullPath = os.path.join(dirPath, file)
        if os.path.exists(fullPath):
            sdPath = f'/atmosphere/exefs_patches/{projName}/{file}'
            print(f'Sending "{sdPath}" to {consoleIP}.')
            ftp.storbinary(f'STOR {sdPath}', open(fullPath, 'rb'))
            if isNeedOtherSwitch:
                print(f'Sending "{sdPath}" to {altSwitchIP}.')
                otherftp.storbinary(f'STOR {sdPath}', open(fullPath, 'rb'))

# ensuredirectory(ftp, '/atmosphere', 'contents')
# ensuredirectory(ftp, '/atmosphere/contents', '0100000000010000')
# ensuredirectory(ftp, f'/atmosphere/contents/0100000000010000', 'exefs')

binaryPath = f'starlight_patch_100/atmosphere/contents/0100000000010000/exefs/subsdk1'

if os.path.isfile(binaryPath):
    sdPath = f'/atmosphere/contents/0100000000010000/exefs/subsdk1'
    print(f'Sending "{sdPath}" to {consoleIP}.')
    ftp.storbinary(f'STOR {sdPath}', open(binaryPath, 'rb'))
    if isNeedOtherSwitch:
        print(f'Sending "{sdPath}" to {altSwitchIP}.')
        otherftp.storbinary(f'STOR {sdPath}', open(binaryPath, 'rb'))
