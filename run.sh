#!/bin/bash
#File Name : run
#Author       : Raja Shekar 

#user compilation in sequence

	read -p "do u want to compile the myapp.c :[y/n] :" choice
	if [ $choice == 'y' ]; then
		make clean
			if (make)then
			echo "compilation sucessful"
			read
			fi
		ls -ll	
	fi	
	read -p "Do u want to insert the node :[y/n] :" choice
	if [ $choice == 'y' ]; then
		sudo insmod ./modules/MyCharDev.ko
		echo -e "Module has been inserted\n"
		lsmod | grep MyCharDev	
		read 
		cat /proc/devices | grep MyCharDev 
		echo "please enter major number"
		read major
		echo "sudo mknod ./MyCharDev c major minor"
		sudo mknod -m 666 ./MyCharDev c $major 0	# -m is used to change the mode of the file to given mode no
		cat /proc/devices | grep MyCharDev
#		sudo chmod 666 MyCharDev
		ls -l MyCharDev
		read
	fi	
	read -p "Do u want to run the application :[y/n]" choice
	if [ $choice == 'y' ]; then
		gcc myapp.c
		echo "a.out file created"
		./a.out
#		read
		dmesg 
	fi
	sudo rmmod MyCharDev
	dmesg
	ls -l
	echo -e "unlinking the VFS\n"
	unlink MyCharDev
	ls -l
	make clean
	rm ./a.out
echo "running script is completed"
