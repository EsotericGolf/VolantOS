chmod 0777 ./volant/bin/volant

clear

if ! ./volant/bin/volant compile main.vo -clang "-g -I../memory -I.. ../memory/gc.c -Ivolant/lib/internal -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles" -packstructs; then
	exit 1
fi

mv 0main.vo.o OS
mv gc.o OS

cd OS
bash compileos.sh
