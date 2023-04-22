# CN-3

# Task-1 : TCP Client-Server model to reverse a string

## Steps 

### Step 1 :

Run the server.out file \
Commands: \
To compile: gcc server.c -o server.out 
To run: ./server.out 

![image](https://user-images.githubusercontent.com/72215169/233801426-b0b3407f-024c-48fc-96cc-6c6efbe2e709.png)

### Step 2 : 

Run any of the client files (client-1.c , client-2.c , client-3.c , client-4.c , client-5.c ) \
To compile : gcc client-1.c -o client.out \
To run: ./client.out 

Input the string you want to send to the server. 

![image](https://user-images.githubusercontent.com/72215169/233801486-964841d2-c15d-4977-b39c-8fc0d8c930ce.png)

# Task-2 : TCP Client-Server model for Ticket Reservation 

## Steps 

### Step 1 :

Run the server.out file \
Commands: \
To compile: gcc server.c -o server.out \
To run: ./server.out \

Enter the credentials : \
User_id : admin \
Password : password \

![image](https://user-images.githubusercontent.com/72215169/233801652-d2e29a79-e1d8-44b2-912f-b1d10eab4af7.png)

### Step 2 :

Run any of the client files (client-1.c , client-2.c , client-3.c , client-4.c , client-5.c ) \

To compile : gcc client-1.c -o client.out \
To run: ./client.out \


Enter the ticket booking info in this format : \
client-A:B \
where \
A = client id \
B = number of tickets to be booked \


Attached is the screenshot of the process. \
The initial number of tickets 1000 is stored in the server_records.txt file itself. \
[INFO] Tickets Available : 1000 

The initial number of tickets can be changed here in place of 1000 

![image](https://user-images.githubusercontent.com/72215169/233801662-6de93c43-1411-4e90-9c58-680a9cf257e0.png)

After booking through 5 clients, servers_records.txt would look like : 

![image](https://user-images.githubusercontent.com/72215169/233801689-2648b208-5b9e-4cb1-8f27-6b786c945c00.png)


