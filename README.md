# Raspberry Pi Learnings

A collection of notes, experiments, and projects from working with Raspberry Pi.

## Topics

- **Setup & Configuration** – OS installation, headless setup, SSH, Wi-Fi configuration
- **GPIO & Hardware** – LED control, buttons, sensors, PWM
- **Networking** – Static IP, port forwarding, running a home server
- **Projects** – Scripts and mini-projects built on the Pi

## Getting Started

1. Flash Raspberry Pi OS onto an SD card using [Raspberry Pi Imager](https://www.raspberrypi.com/software/)
2. Enable SSH by placing an empty `ssh` file in the boot partition
3. Connect via SSH: `ssh pi@<ip-address>` (default password: `raspberry`)

## Notes

- Default user: `pi`
- Change password on first login: `passwd`
- Update the system: `sudo apt update && sudo apt upgrade -y`
