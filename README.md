

A "$" indicates a command to type into the bash terminal, so "$cd project" means type "cd project"

===============SET UP (ONE TIME THING)===============

Make github account

Put this on flashdrive: http://msysgit.github.io/

On flash drive "Git" folder -> "Git Bash"

$mkdir project

$cd project

$git init

$git config --global user.name "abbott221"

$git config --global user.email "abbottm07@gmail.com"

$git remote add thisURL https://github.com/abbott221/robotRepo.git


===============BEFORE MAKING CHANGES===============

Delete everything in that project folder

On flash drive "Git" folder -> "Git Bash"

$cd project

$git clone https://github.com/abbott221/robotRepo.git

Drag all that stuff in the folder into the corresponding QT Creator folder

Make changes

===============AFTER MAKING CHANGES===============

Drag all that stuff back into the folder on your flashdrive for replacements

Do NOT have a second folder inside the project folder, that seems to cause errors

The .gitignore file handles the .d files, .o files, and extra crap so you don't have to worry about fishing for the files that are uploaded

$git gui

"commit" on toolbar -> "Stage changed files to commit"

Check that the lineup of "staged" files don't contain a bunch of red X's next to them, that means you still need to delete the second folder inside your "project" folder as mentioned above

Type a message for the commit

Press "commit" button

Then, remote ->  push to push code to the internet

Type your username and password

If failed to send,

$git pull thisURL master

Then, press push button again





