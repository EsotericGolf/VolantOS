<!--# Welcome!

This is an x86 operating system written in *(mostly)* Volant(Created for the language jam).

***However,*** I had to modify the compiler heavily as Volant uses blocks instead of regular functions.
I just couldn't get the ***[runtime](https://github.com/mackyle/blocksruntime)*** to play nice and it has dependencies on the standard library which would mean it wont work anyway.

I also added a compiler option to generate structs with the packed attribute to make sure they work for what I needed to use them for.

# Features

Currently, *VolantOS* initializes the **[Global Descriptor Table](https://en.wikipedia.org/wiki/Global_Descriptor_Table)** and the **[Interrupt Descriptor Table](https://en.wikipedia.org/wiki/Interrupt_descriptor_table)**.

That's about it right now, it prints *"Hello World!"* to the screen and fills it with blue if you press a key.

Later on I will implement **[Paging](https://en.wikipedia.org/wiki/Paging)** and memory allocation, potentially followed by basic user programs and keyboard input.
-->
