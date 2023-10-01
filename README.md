[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/Bp585G7b)

Hello, this is the first assignment for the Principles of Distributed Systems. The concept is about Understanding the systems with complex connections. Therefore, I write a client and server software (two separate applications) that interact through the sockets. Thus, I need to start 3 server applications manually.  The client application shall require an input number: when entered, one of the server applications  shall respond with double the entered number.

To run the code: open the terminal(4 window, 1 for client, 3 for server app)
For each window, write the code below:

1.Server1 -> gcc -o server1 server.c
              ./server1 12345 (starting server1 in port 12345)
              
1.Server2 -> gcc -o server2 server.c
              ./server2 12346 (starting server2 in port 12346)
              
1.Server3 -> gcc -o server3 server.c
              ./server3 12347 (starting server3 in port 12347)
              
1.Client -> gcc -o client client.c
              ./client 
              
First, start servers, then client.

After that, write the number you want in the client window, and the system will respond (double number) in a random server.

Testing of server-client application:

<img width="1138" alt="image" src="https://github.com/ADA-GWU/understanding-the-systems-with-complex-connections-alizadeht/assets/78111301/d7fbb447-4dac-422e-8421-d83a5ece167e">



    
