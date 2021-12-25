import os

path = './kroos-attack/'
files = os.listdir(path)
for (idx, file) in enumerate(files):
    # print(file)
    newName = 'kroos-attack-' + str(idx) + '.png'
    # # newName = file + '.png'
    # print(newName)
    os.rename(path+file, path+newName)

    # if file.find(' ') != -1:
    #     i1 = file.find(' ')
    #     i2 = file.find('.')
    #     # print(i1, i2, file[i1:i2])
    #     val = int(file[13:i2])
    #     newName = "copy-kroos-attack-" + str(val-11 if val >= 11 else val+11) + ".png"
    #     print(val, newName)
    #     # newName = 'SkadiRed'+str(int(file[i1+1:i2])-1)+'.png'
    #     os.rename(path+file, path+newName)

    # print(path+file[5:])
    # os.rename(path+file, path+file[5:])
