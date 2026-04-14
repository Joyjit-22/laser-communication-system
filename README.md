# Laser-Based Wireless Communication System (Arduino Li-Fi Prototype)

A wireless digital communication system using light, built with Arduino, a laser module, and an LDR sensor.
This project demonstrates a simplified version of Li-Fi (Light Fidelity) by transmitting text data through laser signals and decoding it on the receiver side.

## Overview

This system replaces traditional wired or RF communication with optical transmission:

- Transmitter: Laser module sends encoded binary data
- Receiver: LDR module detects light and reconstructs data
- Protocol: Custom-designed packet structure for reliable communication

## Features

- Wireless communication using laser light
- Binary encoding (`1 = ON`, `0 = OFF`)
- Custom packet-based protocol:
  - Preamble (synchronization)
  - Start byte
  - Length field
  - Data (ASCII text)
  - End byte
- Shift register-based synchronization (software)
- Real-time keyboard input transmission
- ASCII decoding on receiver side
- Debug mode for bit-level monitoring
- Laser alignment mode (`lon` / `loff`)

## Protocol Structure

```text
[Preamble] 10101010 // Synchronization
[Start]    11110000 // Start of packet
[Length]   XXXXXXXX // Number of data bytes
[Data]     XXXXXXXX // ASCII encoded data
[End]      00001111 // End of packet
```

## Hardware Requirements

- 2 x Arduino Uno (or compatible)
- 1 x Laser module
- 1 x LDR module (with digital output)
- Breadboard and jumper wires

## Circuit Connections

### Transmitter (Laser)

| Component | Arduino |
| --- | --- |
| VCC | 5V |
| GND | GND |
| Signal | Pin 8 |

### Receiver (LDR Module)

| Component | Arduino |
| --- | --- |
| VCC | 5V |
| GND | GND |
| DO | Pin 2 |

## How to Use

### 1. Upload Code

- Upload `sender.ino` to transmitter Arduino
- Upload `receiver.ino` to receiver Arduino

### 2. Align Laser

Open Serial Monitor (sender side), then run:

```text
lon
```

Laser turns on continuously for alignment.

Then run:

```text
loff
```

This switches back to transmission mode.

### 3. Send Message

Type any message in Serial Monitor, for example:

```text
hello
```

### Receiver Output

```text
PACKET RECEIVING
Length: 5
Message: hello
```

## How It Works

1. Input text is converted into ASCII binary.
2. Laser transmits bits using ON/OFF signals.
3. LDR detects light changes and outputs a digital signal.
4. Receiver samples bits using fixed timing.
5. Shift register detects the preamble for synchronization.
6. Packet is decoded and converted back to text.

## Limitations

- Sensitive to ambient light interference
- Requires precise alignment
- Limited speed due to LDR response time
- Works best in controlled lighting conditions
- Serial Monitor does not support Unicode (emoji)

## Future Improvements

- Increase transmission speed
- Add checksum/error detection
- Implement Manchester encoding
- Build full-duplex communication system
- Replace LDR with photodiode for better performance
- Develop GUI interface (Python or web-based)

## Author

Your Name

## Support

If you found this project useful, consider giving it a star on GitHub.