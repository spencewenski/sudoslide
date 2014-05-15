sudoslide
=========

A Rubik's Cube-esque sliding puzzle

## Available commands  
slide_col \<board_id\> \<col_num\> \<slide_amount\> - slide a column up or down;
positive slide_amount for up, negative for down; error: board does not exist,
column does not exist  

slide_row \<board_id\> \<row_num\> \<slide_amount\> - slide a row right or left;
positive slide_amount for right, negative for left; error: board does not exist,
row does not exist  

add_board  
remove_board  
restore_original  
solve_board  
show  
open_list_view  
close_list_view  
