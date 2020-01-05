#!/bin/bash


if [ "$1" != "" ];then 
	svnproject=$1
else
	svnproject="svntest"
fi

FileChange()
{
	Config_file1="/home/svn/$svnproject/conf/svnserve.conf"
	Config_file2="/home/svn/$svnproject/conf/passwd"
	Config_file3="/home/svn/$svnproject/conf/authz"

	sudo chmod 666 $Config_file1
	sudo chmod 666 $Config_file2
	sudo chmod 666 $Config_file3

	sudo sed -i 's/# auth-access = write/auth-access = write/g' $Config_file1
	sudo sed -i 's/# anon-access = read/anon-access = none/g' $Config_file1
	sudo sed -i 's/# authz-db = authz/authz-db = authz/g' $Config_file1
	sudo sed -i 's/# password-db = passwd/password-db = passwd/g' $Config_file1

	sudo echo ' ' >> $Config_file2 	
	sudo echo 'svntest = svntest' >> $Config_file2 	

	sudo echo 'admin = svntest' >> $Config_file3
	sudo echo ' ' >> $Config_file3
	sudo echo ' ' >> $Config_file3  
	sudo echo '[/]' >> $Config_file3 
	sudo echo '@admin = rw' >> $Config_file3 
}


# apt-get install subversion
sudo mkdir -p /home/svn/$svnproject
sudo svnadmin create /home/svn/$svnproject
FileChange
sudo killall svnserve 
sudo svnserve -d -r /home/svn

echo "please enter this cmd !!!"
echo " "
echo "sudo chmod 777 -R /home/svn;sudo chmod 777 -R /home/svn/$svnproject/db"
