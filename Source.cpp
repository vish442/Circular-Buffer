#include <iostream>
#include <ctime>
using namespace std;

// The format of the messages in the buffer
struct Message {
    unsigned char data;  // Single byte of information to be sent
    time_t timestamp;    // Number of seconds since 1 January 1970
};

// The length of the fixed array
#define BUFFER_LENGTH 10

// Function prototypes
void Produce(Message*, unsigned long&, unsigned long&);
void Consume(Message*, unsigned long&, unsigned long&);
void Show(const Message*, unsigned long, unsigned long);

// Control the entering, sending, and displaying of messages in the buffer
// Arguments: None
// Returns: 0 on completion
int main() {
    Message buffer[BUFFER_LENGTH];    // The message buffer
    unsigned long buffer_tail = 0;    // Position of the tail in the message buffer
    unsigned long buffer_length = 0;  // Number of messages in the buffer
    char UserInput;

    // Loop until the user wishes to exit
    while (1) {
        // Show the menu of options
        cout << endl;
        cout << "Buffer Management Menu" << endl;
        cout << "----------------------" << endl;
        cout << "1. Produce a new message for the buffer" << endl;
        cout << "2. Consume a message from the buffer" << endl;
        cout << "3. View the contents of the buffer" << endl;
        cout << "4. Exit from the program" << endl << endl;

        // Get the user's choice
        cout << "Enter your option: ";
        cin >> UserInput;
        cout << endl;

        // Act on the user's input
        switch (UserInput) {
        case '1':
            Produce(buffer, buffer_tail, buffer_length);
            break;

        case '2':
            Consume(buffer, buffer_tail, buffer_length);
            break;

        case '3':
            Show(buffer, buffer_tail, buffer_length);
            break;

        case '4':
            return 0;

        default:
            cout << "Invalid entry" << endl << endl;
            break;
        }
    }
}

// Produce a new message and add it to the head of the buffer
// Arguments:
//   (1) start of the buffer
//   (2) position of the tail of the buffer
//   (3) number of messages in the buffer
// Returns: void
void Produce(Message* buffer, unsigned long& buffer_tail, unsigned long& buffer_length) {
    if (buffer_length >= BUFFER_LENGTH) {
        cout << "Buffer overflow! Cannot add more messages." << endl;
        return;
    }

    unsigned long buffer_head = (buffer_tail + buffer_length) % BUFFER_LENGTH;

    // Get the value of the data for the message from the user
    cout << "Type in the message you wish to store (single character): ";
    cin >> buffer[buffer_head].data;
    cout << endl;

    // Get the current time for the message
    buffer[buffer_head].timestamp = time(NULL);

    // Adjust the buffer length
    buffer_length++;
}

// Consume the message at the tail of the buffer
// Arguments:
//   (1) start of the buffer
//   (2) position of the tail of the buffer
//   (3) number of messages in the buffer
// Returns: void
void Consume(Message* buffer, unsigned long& buffer_tail, unsigned long& buffer_length) {
    // If the buffer is empty, display an error statement
    if (buffer_length == 0) {
        cout << "Buffer is empty!" << endl;
        return;
    }

    // Display the message at the tail
    cout << "Consumed message: " << buffer[buffer_tail].data << endl;

    // Remove the message by advancing the tail of the buffer in a circular manner
    buffer_tail = (buffer_tail + 1) % BUFFER_LENGTH;
    buffer_length--;
}

// Display all of the messages in the buffer
// Arguments:
//   (1) start of the buffer
//   (2) position of the tail of the buffer
//   (3) number of messages in the buffer
// Returns: void
void Show(const Message* buffer, unsigned long buffer_tail, unsigned long buffer_length) {
    if (buffer_length == 0) {
        cout << "Buffer is empty!" << endl;
        return;
    }

    cout << "Buffer contents:" << endl;
    for (unsigned long i = 0; i < buffer_length; ++i) {
        unsigned long index = (buffer_tail + i) % BUFFER_LENGTH;
        cout << "Message: " << buffer[index].data << " (Timestamp: " << buffer[index].timestamp << ")" << endl;
    }
}
