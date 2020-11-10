# Module 05

## Bit-Banding
### Read-Modify-Write
### Interrupts
### What is Bit-Banding
- Special feature introduced in Cortex-M3
- Provides atomic operation to **bit** data
- Bit-Banding Regions covers the following:
  - 0x20000000-0x200FFFFF in SRAM
  - 0x40000000-0x400FFFFF for peripherals
- Each bit has a corresponding `alias address`
- Writing to an `alias address` has the same effect as RMW operation

### Mapping Bit-Banding Addressses
| Address range         | Memory region              | Instruction and data accesses                                                                                                                           |
|-----------------------|----------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------|
| 0x20000000-0x200FFFFF | SRAM bit-band region       | Direct accesses to this memory range behave as SRAM memory accesses, but this region is also bit addressable through bit-band alias.                    |
| 0x22000000-0x23FFFFFF | SRAM bit-band alias        | Data accesses to this region are remapped to bit band region. A write operation is performed as read-modify-write. Instruction acceses are not remapped |
| 0x40000000-0x400FFFFF | Peripheral bit-band alias  | Direct accesses to this momory range behave as peripheral memory accesses, but this region is also bit addressable through bit-band alias.
| 0x42000000-0x43FFFFFF | Peripheral bit-band alias  | Data accesses to this region are remapped to bit band region. A write operation is performed as read-modify-write. Instruction acceses are not remapped |

### Bit-Band mapping calculation
A mapping formula shows how to reference each word in the alias region to a corresponding bit in the bit-band region. The mapping formula is:
```bit_word_addr = bit_band_base + (byte_offset * 32) + (bit_number * 4)```
where:
- `bit_word_addr` is the address of the word in the alias memory region that maps to the targeted bit
- `bit_band_base` is the starting address of the alias region
- `byte_offset` is the number of the byte in the bit-band region that contains the targeted bit
- `bit_number` is the bit position (0-7) of the targeted bit

### Demonstration
```C
// set a bit
*((unsigned int*)(0x42000000 + (0x2104C * 32) + (1 * 4))) = 0x1;
// clear a bit
*((unsigned int*)(ox42000000 + (0x2104C * 32) + (1 * 4))) = 0x0;
```


## C Programming (continued)
### Arrays & Pointers
### Functions and the C-Stack


## Building a FIFO

### FIFO Requirements
1. Implement a FIFO Queue data structure in C
2. FIFO has a predefined size
3. FIFO supports `char` data types
4. Provide function to put a new char data into FIFO
5. Provide function to get the oldest element from FIFO
6. Provide function to check if FIFO is empty
7. Provide function to check if FIFO is full
8. Return error (-1) if attempting to add a new element when FIFO is full
9. Return error (-1) if attempting to retrieve and element from an empty FIFO
10. Return (0) for success

### FIFO API
```C
int queue_put(char data);
// Return value used to indicate error or success

int queue_get(char* data);
// Return value used to indicate error or success
// data is also used as a return value

void queue_init(void);
```

### FIFO Design
- Array backend
- Two pointers
  - PUTPT tracks where to add the next element in the queue
  - GETPT trackes where to retrieve from the queue

### FIFO Implementation
### FIFO Testing
#### Arrange, Act, Assert
- Arrange describes the setup needed for the test
- Act invokes the actions of the test
- Assert describes the verification of the test

```C
// Arrange (setup)
queue_init();
// Act (execute)
queue_put('A');
// Assert (verify)
assert(0 == queue_get(&testChar));
assert('A' == testChar);
```

### FIFO Code
```C
#include <assert.h>
#define QUEUE_SIZE 5

char QueueStore[QUEUE_SIZE];

char* putPtr;
char* getPtr;

void queue_init(void)
{
  putPtr = getPtr = QueueStore;
}

int queue_put(char data)
{
  *putPtr = data;
  return 0;
}

int queue_get(char* data)
{
  *data = *getPtr;
  return 0;
}

int main()
{
  // test 01
  int result;
  char actualData;
  // Arrange
  queue_init();
  // Act
  result = queue_put('A');
  queue_get(&actualData);
  // Assert
  assert(0 == result);
  assert('A' == actualData);

  return 0;
}
```
