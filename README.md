# CN-3

# Task-1 : TCP Client-Server model to reverse a string

## Steps 

### Step 1 :

Run the server.out file \
Commands: \
To compile: gcc server.c -o server.out 
To run: ./server.out 

![image](https://user-images.githubusercontent.com/72215169/233819678-a0a13fa8-5824-4beb-9a30-caf751f971d5.png)


### Step 2 : 

Run any of the client files (client-1.c , client-2.c , client-3.c , client-4.c , client-5.c ) \
To compile : gcc client-1.c -o client.out \
To run: ./client.out 

Input the string you want to send to the server. 

![image](https://user-images.githubusercontent.com/72215169/233819696-4111912a-e81c-47e8-a5b3-afe1e5641233.png)



# Task-2 : TCP Client-Server model for Ticket Reservation 

## Steps 

### Step 1 :

Run the server.out file \
Commands: \
To compile: gcc server.c -o server.out \
To run: ./server.out 

Enter the credentials : \
User_id : admin 
Password : password 

![image](https://user-images.githubusercontent.com/72215169/233819719-90b1867a-b107-43a5-b9a1-9c39d862a40d.png)

### Step 2 :

Run any of the client files (client-1.c , client-2.c , client-3.c , client-4.c , client-5.c ) \

To compile : gcc client-1.c -o client.out \
To run: ./client.out 

Enter the number of tickets booked :

![image](https://user-images.githubusercontent.com/72215169/233819770-65f5061a-aafb-4d99-87d3-7f3e324b22e1.png)


Attached is the screenshot of the process. \
The initial number of tickets 1000 is stored in the server_records.txt file itself. \
[INFO] Tickets Available : 1000 

The initial number of tickets can be changed here in place of 1000 

![image](https://user-images.githubusercontent.com/72215169/233819817-010335d6-51a6-42f9-904f-249b8cf35dc4.png)

After booking through 5 clients, servers_records.txt would look like : 

![image](https://user-images.githubusercontent.com/72215169/233819958-dae4aa33-8c0f-4fdd-8e03-41d6d904704c.png)


