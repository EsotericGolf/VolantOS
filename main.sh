clear

if ! genisoimage --help 2> /dev/null; then
	install-pkg genisoimage
fi

if ! nasm -h > /dev/null; then
	install-pkg nasm
fi

cd qemu

if ! qemu-system-i386 -h 2> /dev/null; then
	install-pkg qemu
fi

cd ..

cp main.vo VolantOS

cd VolantOS
bash main.sh

cp OS/iso/boot/kernel ../qemu

mv OS/os.iso ..

cd ../qemu

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. qemu-system-i386 -kernel kernel
