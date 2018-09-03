1. Normal Mode:
	1.To scroll you can use UP and DOWN arrow key.
	2.Press ENTER to open file or directory.
	3.To go backward press LEFT arrow key.
	4.To go forward press RIGHT arrow key.
	5.To go to root directory press "h" key.
	6.To go to parent directory press BACKSPACE.
	7.To enter Command Mode press ":" key.
	8.If you see unusual contents on the screen press "r" to reprint the screen.
	9.To quit the application press "q".
	
2. Command Mode​ :
	NOTE:Path to be given to any command should be absolute according to the root and start with "~/".
	NOTE: In case of copy or move if destination already contains files that you are trying move/copy they will be skeeped i.e. won't get overwrite.
	NOTE: FileName should not contain spaces.

	1.Copy ‘:copy <source_file(s)> <destination_directory>’

	2.Move ‘:move <source_file(s)> <destination_directory>’

	3.Rename ‘:rename <old_filename> <new_filename>’
		NOTE: rename command won't take path.
		NOTE: you should use file name only.

	a. Ex- :copy foo.txt bar.txt baz.mp4 ~/foobar
	   Ex- :move foo.txt bar.txt baz.mp4 ~/foobar
	   Ex-:rename foo.txt bar.txt

	4. Create file ‘:create_file <file_name> <destination_path>’

	5. Create directory ‘:create_dir <dir_name> <destination_path>’

	a. Ex- :create_file foo.txt ~/foobar
	   Ex- :create_file foo.txt .
	   Ex- :create_dir folder_name ~/foobar

	6. Goto ‘:goto <location>’
	   Ex- :goto <directory_path>

	7. Search a file or folder given full filename.
	   Command ​ ‘:search <filename>’
	
	8. Snapshotting the filesystem and dump into a file
	   Command ‘​ :snapshot <folder> <dumpfile>​ ’

	9. on typing ‘esc’ and press ENTER the application goes to Normal Mode.
	
	10. To close the application type "exit" and press enter.
