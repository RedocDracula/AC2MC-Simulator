README

CS-204 project, RISC-V SIMULATOR, GROUP 13:-
Languages:- C++, Electron JavaScript 

Team members : 
            [Harshit Malik](https://github.com/HarshitMalik)   :- 2017csb1078
            [Hersh Dhillon](https://github.com/hershd23)    :- 2017csb1079
            [Jeetu Kumar](https://github.com/i-am-g2)      :- 2017csb1083
            [Shreekanth Ajith](https://github.com/RedocDracula) :- 2017csb1110
            [Nilansh Rajput](https://github.com/Nilanshrajput)   :- 2017csb1092


HOW TO RUN:-
        On the terminal :-

        g++ -o executable main.cpp
        ./executable

        On the GUI:-
            Instructions coming soon

Phase 1:-
Parsed the input file
                input.txt to input1.txt for assembler directives
                input1.txt to basicCode.txt for the basic code 
                basicCode.txt to machineCode.txt for the machine code

Phase 2:-
Implemented data path and control paths to run the Instructions.
Implemented all stages i.e. Fetch, Execute, Decode, Memory, Writeback
Implemented inter state buffers, memory unit and register files for the same

Phase 3:-
Implemented pipeline structure with and without data forwarding

Phase 4:-
Implemented data and instruction caches

Features:-
    Functionality to switch between 
        1. Non- pipelined
        2. Pipelined with stalls
        3. Pipelined with Data forwarding
    
    Functionality to output register values and values of the inter state buffers

    Functionality to run cycle by cycle

    Give out number of mispredictions, number of stalls etc.

    Print register values and inter state buffers after every cycle.

Instructions not supported:-
    - auipc, lui and pseudo instructions not handled.
    - Assumption, code would be free of the syntax errors.

Direct Mapping was implemented for the data and instruction caches.

GUI :- Electron framework
            - Node JS backend
            - HTML CSS frontend
