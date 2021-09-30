mkdir ~/.todo
touch ~/.todo/list.td

gcc main.c -o todo tasks.c lista.c
chmod +x todo
sudo cp todo /bin
rm todo
