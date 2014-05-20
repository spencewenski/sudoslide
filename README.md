Sudoslide
===============================

A Rubik's Cube-esque sliding puzzle

Description
-------------------------------
Sudoslide is a sliding-based puzzle game. It features puzzle mechanics similar
to a Rubik's cube: trying to solve one part of the puzzle might mess up other
parts. A board starts out scrambled, and the goal of the game is to rearrange 
the numbers on the board so they are in order. For example, 
for a board of size 4, it would start out looking something like this:  

     4  3 10  1  
    11  2  8  5  
     6 12  7 13  
    14  9 15  0  

and the solved board would look like this:  

     0  1  2  3  
     4  5  6  7  
     8  9 10 11  
    12 13 14 15  

Available commands
-------------------------------
```slide_col <board_id> <col_num> <slide_amount>```  
	slide a column up or 
  down; positive slide_amount for up, negative for down; error: board does not 
  exist, column does not exist, unable to read integer values

```slide_col <board_id> <col_num> <slide_amount>```  
	slide a column up or 
	down; positive slide_amount for up, negative for down; error: board does not 
	exist, column does not exist, unable to read integer values  

```slide_row <board_id> <row_num> <slide_amount>```  
	slide a row right or 
	left; positive slide_amount for right, negative for left; error: board does not 
	exist, row does not exist, unable to read integer values  

```add_board <board_size>```  
	create a new board of the specified size 
	and add to the appropriate views  

```remove_board <board_id>```  
	remove a board from the game; error: board does
	not exist, unable to read integer value  

```restore_original <board_id>```  
	restore a board to its original state;
	error: board does not exist, unable to read integer value  

```solve_board <board_id>```  
	solve the board step by step from original state;
	error: board does not exist, unable to read integer value  

```show```  
	display all the open views  

```open_list_view``` 
	open the list view; error: list view already open  

```close_list_view```  
	close the list view; error: list view is not open  
