# Control of a Four-Floor Smart Elevator

## Introduction

This project involved the implementation of an elevator algorithm with statistical analysis, fault 
detection, and Ethernet/IP communication for a four-floor smart elevator.

The Ladder logic programs for the control of a four-floor smart elevator were
developed using Studio 5000 Logix Designer® on Allen-Bradley 1769-L30ER CompactLogix™ PLCs. It was 
programmed with general instructions, subroutines, tasks, UDTs and AOIs to process the inputs 
captured from limit switches and pushbuttons on a pre-built workbench to actuate indicator lights, 
solenoid, motor, and relay, based on its algorithm.

The purpose of this project was to get familiarized with the reference manual and to apply lecture 
materials in a real-world industrial setting by writing programs that are clear and easy to expand.

## Workstation

<table>
	<tr>
		<td><img src="https://raw.githubusercontent.com/tylim2946/BCIT/main/ROBT4456-PLC-Applications/FinalProject/Photos/workstation.jpg" width="450" height="600"></td>
		<td><img src="https://raw.githubusercontent.com/tylim2946/BCIT/main/ROBT4456-PLC-Applications/FinalProject/Photos/input_output_table.jpg" width="450" height="600"></td>
	</tr>
</table>

## State Diagram

<table>
	<tr>
		<td><img src="https://raw.githubusercontent.com/tylim2946/BCIT/main/ROBT4456-PLC-Applications/FinalProject/StateDiagram/main_elevator_logic.jpg" width="480" height="270"></td>
		<td><img src="https://raw.githubusercontent.com/tylim2946/BCIT/main/ROBT4456-PLC-Applications/FinalProject/StateDiagram/door_control.jpg" width="350" height="270"></td>
	</tr>
</table>

## HMI

X2 pro 7 B2 by Beijer Electronics with iX Developer software was used to implement HMI.

<table>
	<tr>
		<td><img src="https://raw.githubusercontent.com/tylim2946/BCIT/main/ROBT4456-PLC-Applications/FinalProject/Screenshots/Overview.png" width="480" height="288"></td>
		<td><img src="https://raw.githubusercontent.com/tylim2946/BCIT/main/ROBT4456-PLC-Applications/FinalProject/Screenshots/Emergency.png" width="480" height="288"></td>
	</tr>
  <tr>
		<td><img src="https://raw.githubusercontent.com/tylim2946/BCIT/main/ROBT4456-PLC-Applications/FinalProject/Screenshots/Diagnostics.png" width="480" height="288"></td>
		<td><img src="https://raw.githubusercontent.com/tylim2946/BCIT/main/ROBT4456-PLC-Applications/FinalProject/Screenshots/Administration.png" width="480" height="288"></td>
	</tr>
  <tr>
		<td><img src="https://raw.githubusercontent.com/tylim2946/BCIT/main/ROBT4456-PLC-Applications/FinalProject/Screenshots/LogIn.png" width="480" height="288"></td>
		<td><img src="https://raw.githubusercontent.com/tylim2946/BCIT/main/ROBT4456-PLC-Applications/FinalProject/Screenshots/Settings.png" width="480" height="288"></td>
	</tr>
  <tr>
		<td><img src="https://raw.githubusercontent.com/tylim2946/BCIT/main/ROBT4456-PLC-Applications/FinalProject/Screenshots/Dialog.png" width="480" height="288"></td>
	</tr>
</table>
