# FileBrowser
## Browser
This program is supposed to do basic operations in your filesystem. We can browser in filesystem and use commands like delete, move, copy, mkdir, maketxt, makelink and size.

### Commands
Delete : takes one parameter and that is path to folder/file we want to delete or simple name of sub-file/folder of currently opened folder.
Move : takes 2 parameters, from and where are we moving. Can take just names of sub-file/folder of currently opened folder.
Copy : takes 2 parameters, from and where are we copying. Can take just names of sub-file/folder of currently opened folder.
mkdir : creates folder or tree of folder in currently opened diretory.
maketxt : creates txt file that we can also write to or if the name is already used we will read that txt file.
makelink : takes 2 parameters, from and where are we are creating link. Can take just names of sub-file/folder of currently opened folder.
size : prints out size of currently opened directory.

## Operations using regular expressions
This program can also delete, move and copy files using regular expressions. 
### Example
delete /home/test/ .* - this command will delete all content of /home/test/ folder
delete /home/test/ .*[.]txt - this will delete only .txt files in /home/test/ folder
move /home/test/ Makefil. - this will move all files/folder that starts with Makefil? and are followed by any other character from /home/test/ folder 
  /home/test2/ -> into this folder that is taken as 2nd parameter
copy works exactly the same as move but copies files

#### Documentation of classes etc can be found at $(BUILD_FOLDER)/doc/index.html
