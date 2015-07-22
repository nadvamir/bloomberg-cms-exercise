# Commodity Market System (CMS<GO>)

## Author

Maksim Solovjov

## Description

This is a mock trading system allowing dealers to post commodity orders and then trade on them. The system provides both command line and network interface.

## Implemented parts

Full exercise is completed, with both extensions.

## Used libraries

pthread and unix sockets.

## Usage

```bash
# to build the system:
make
# to build the tests:
make test
# cleanup:
make clean
```

To run the system in console I/O mode, type

```bash
./cms base
```

To run the system in socket communication mode that only allows one connection, type

```bash
./cms ext1 <port>
```

To run the system in socket communication mode that allows multiple connections, type

```bash
./cms ext2 <port>
```

To run the tests type

```bash
./tests.exe
```

The following is a shortlist of commands, recognised by the main application:

```
<dealer> = (JPM|BARX|DB|CITI|RBS...)
<commodity> = (GOLD|SILV|PORK|OIL|RICE)

<dealer> POST (BUY|SELL) <commodity> <amount:int> <price:double>

<dealer> REVOKE <orderId:int>

<dealer> CHECK <orderId:int>

<dealer> AGGRESS <orderId:int> <amount:int>

<dealer> LIST [<commodity> [<dealer>]]
```

## Personal goals

In completing this exercise I tried to achieve the following:

* Examine TDD as a design technique and investigate its applicability to C++.
* Make use of at least some of advanced meta-programming concepts outlined in Alexandrescu's "Modern C++ Design" book. If it takes so much mental effort to read, you should better learn something...
* Learn to use STL for everything I can.
* Practice implementing the command pattern.
* Investigate how different designs of basic building blocks (Commodity, Dealer, and Order::Side) affect the overall program.

## Design of the system

I used test-driven development as a design technique when writing this code, so there was no strong initial preconception on how this system will look. In the following state of program, these are the main entities.

### Repository layout

* include/ -> all the header files, but also most of the implementation, since the code was heavily inlined to speed up the development.
* src/ -> occasional *.cpp files + main.cpp
* test/ -> all GoogleMock tests. Base exercise was test-driven, and thus is thoroughly tested. I did not write tests for networking and multithreading code due to the lack of time.

### Data

1. Commodity -> abstract base for different commodities
2. Dealer -> a class representing a dealer
3. Order -> stores full order information
4. OrderStore -> a "database"

### Logic

1. parseMessage() -> function that parses the input and returns a Command
2. Command -> abstract base for different commands, operator() of whom returns a Message
3. Message -> abstract base for output messages
4. various runtime errors -> used to display errors
5. Chanel -> abstract base for hiding the source of input, allowing to work both with console and network

### Utility

1. SharedPtr -> because C++03. Ref-counted smart pointer that can be either thread-safe or not.
2. CopyIf -> identical to C++11 <algorithm> copy_if.

### Networking

1. Socket -> a wrapper around sys/socket.h
2. NetworkChanel -> a very basic input/output wrapper for a socket connection

### Threading
1. Lock -> a lock guard for pthread_mutex_t
2. ThreadPool -> a thread pool
3. WorkQueue -> a queue for dispatching connections to worker threads
4. worker function -> consumes connections while the queue is dispatching them to it

## Notable design decisions

I chose to implement thread safety via SharedPtr. I was already using SharedPtr everywhere to manage memory, so I created a thread-safe specification and used it for OrderStore and Order. This specification relies on a temporary locking object trick: operator-> returns an lock object on a shared mutex that provides its own operator->, and this object exists throughout the statement in which SharedPtr::operator-> is used. Effectively, since all access to OrderStore and Order is done through operator-> of a SharedPtr, this is equivalent to making all of their members synchronized.

Another shared resource, WorkQueue, handles thread-safety internally because it needs to do more with threads. The work queue is a standard concurrent queue apart from its ability to terminate work threads gracefully. Pop() operation on it returns false if the last worker thread has finished its work and the queue is empty. This requires a worker thread to notify the queue after servicing of each connection.

Using a command pattern allowed to bar the main program logic from each individual request details. A command needs to be provided with a pointer to OrderStore, which is handled by the main glue logic. Executing the command will either return a Message, which can be streamed to the output Chanel, or it will throw an exception, which is also streamed. Use of locks and smart pointers allows the code to be exception friendly.

Finally, a simple recursive-descent parser that builds a command internally allowed to provide a uniform interface to the input.

Full application logic is contained within src/main.cpp

## Known bugs

1. NetworkChanel is too simplistic for real network communication. It works well with telnet on localhost, but it does not deal with real issues of networked messages, such as them arriving in parts or lumped together.

2. AGGRESS command does not support the list form, you can only aggress on one order at a time.

3. You can AGGRESS on your own orders.
