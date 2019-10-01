import random as rnd
import os
import sys

class Grid():
    def __init__(self, row=4, col=4, initial=2):
        self.row = row                              # number of rows in grid
        self.col = col                              # number of columns in grid
        self.initial = initial                      # number of initial cells filled
        self.score = 0

        self.grid = self.createGrid(row, col)       # creates the grid specified above

        self.emptiesSet = []                        # list of empty cells
        self.updateEmptiesSet()

        for _ in range(self.initial):               # assign two random cells
            self.assignRandCell(init=True)


    def createGrid(self, row, col):

        """
        Create the grid here using the arguments row and col
        as the number of rows and columns of the grid to be made.

        The function should return the grid to be used in __init__()
        """
        grid = [] # creating the grid object 
        for i in range(row):
            rows = [0]*col    
            grid.append(rows)
        return grid
            
            
    def assignRandCell(self, init=False):

        """
        This function assigns a random empty cell of the grid
        a value of 2 or 4.

        In __init__() it only assigns cells the value of 2.

        The distribution is set so that 75% of the time the random cell is
        assigned a value of 2 and 25% of the time a random cell is assigned
        a value of 4
        """

        if len(self.emptiesSet):
            cell = rnd.sample(self.emptiesSet, 1)[0]
            if init:
                self.grid[cell[0]][cell[1]] = 2
            else:
                cdf = rnd.random()
                if cdf > 0.75:
                    self.grid[cell[0]][cell[1]] = 4
                else:
                    self.grid[cell[0]][cell[1]] = 2
            self.emptiesSet.remove(cell)

    def drawGrid(self):

        """
        This function draws the grid representing the state of the game
        grid
        """
        for row_index in range(self.row):
            line = '\t|'
            for col_index in range(self.col):
                if not self.grid[row_index][col_index]:
                    line += ' '.center(5) + '|'
                else:
                    line += str(self.grid[row_index][col_index]).center(5) + '|'
            print(line)
        print()

    def updateEmptiesSet(self):
    
        """
        This function should update the list of empty tiles of the grid.
        #"""
        self.emptiesSet = []
        for row in range(len(self.grid)):
            for col in range(len(self.grid[0])):    
                if self.grid[row][col] == 0:
                    self.emptiesSet.append([row,col])
    
    def collapsible(self):
        
        """
        This function should test if the grid of the game is collapsible
        in any direction (left, right, up or down.)
        
        It should return True if the grid is collapsible.
        It should return False otherwise.
        """
        for row in range(self.row):
            for col in range(self.col):
                if len(self.emptiesSet) > 0: # first check is there are any empty cells in the grid
                    return True
                elif col < self.col - 1 and self.grid[row][col] == self.grid[row][col+1]: # then check from columns on the right
                    return True
                elif row < self.row - 1 and self.grid[row][col] == self.grid[row + 1][col]: # check for rows on the bottom
                    return True  
        return False
    
    def collapseRow(self, lst):
    
        """
        This function takes a list lst and collapses it to the LEFT.
        
        This function should return two values:
        1. the collapsed list and
        2. True if the list is collapsed and False otherwise.
        """  
        # We will work on 'alist': a copy of our original lst and check if it is collapsible or not giving the required bool (True or False)
        alist = lst.copy()
        for i in range(len(alist)):
            if 0 in alist:
                # remove the zeros from the list first and append it at the end
                alist.remove(0)   
                alist.append(0)
        for i in range(len(alist)):
            if i < len(alist)-1 and alist[i] == alist[i+1] :
                alist[i] += alist[i+1]
                self.score += alist[i]
                alist[i+1] = 0
            if 0 in alist:
                # remove the zeros from the list first and append it at the end
                alist.remove(0)   
                alist.append(0)            
        if alist == lst:
            return alist, False
        else:
            return alist, True
       

    def collapseLeft(self):
    
        """
        This function should use collapseRow() to collapse all the rows 
        in the grid to the LEFT.
        
        This function should return True if any row of the grid is collapsed 
        and False otherwise.
        """
        collapsible = False
        for index in range(self.row):
            collapsed_row,collapsed = self.collapseRow(self.grid[index]) 
            # taking the output from collapseRow() with the a row from self.grid as its argument
            if collapsed:
                collapsible =  True
                self.grid[index] = collapsed_row
        return collapsible

    def collapseRight(self):
    
        """
        This function should use collapseRow() to collapse all the rows 
        in the grid to the RIGHT.
        
        This function should return True if any row of the grid is collapsed 
        and False otherwise.
        """
        collapsible = False
        for index in range(self.row):
            reverse_row = list(reversed(self.grid[index])) # reversing the row for the opposite implementation
            collapsed_row,collapsed = self.collapseRow(reverse_row) # taking the output from collapseRow() with the reversed row as its argument
            if collapsed:
                collapsible = True
                self.grid[index] = list(reversed(collapsed_row))
        return collapsible

    def collapseUp(self):
    
        """
        This function should use collapseRow() to collapse all the columns
        in the grid to UPWARD.
        
        This function should return True if any column of the grid is 
        collapsed and False otherwise.
        """
        collapsible = False
        # converting columns into rows
        rows = [[self.grid[j][i] for j in range(len(self.grid))] for i in range(len(self.grid[0]))] 
        for index in range(len(rows)):
            collapsed_row,collapsed = self.collapseRow(rows[index]) 
            # taking the output from collapseRow() with the row as its argument
            if collapsed:
                collapsible =  True
                rows[index] = collapsed_row
        #converting the rows back into columns again
        self.grid = [[rows[j][i] for j in range(len(self.grid[0]))] for i in range(len(self.grid))] 
        return collapsible

    def collapseDown(self):

        """
        This function should use collapseRow() to collapse all the columns
        in the grid to DOWNWARD.
        
        This function should return True if any column of the grid is 
        collapsed and False otherwise.
        """
        collapsible = False
        # converting columns into rows        
        rows = [[self.grid[j][i] for j in range(len(self.grid))] for i in range(len(self.grid[0]))] 
        for index in range(len(rows)):
            reverse_row = list(reversed(rows[index])) # reversing the row for the opposite implementation           
            collapsed_row,collapsed = self.collapseRow(reverse_row) 
            # taking the output from collapseRow() with the reverse_row as its argument
            if collapsed:
                collapsible =  True
                rows[index] = list(reversed(collapsed_row))
        #converting the rows back into columns again        
        self.grid = [[rows[j][i] for j in range(len(self.grid[0]))] for i in range(len(self.grid))]       
        return collapsible


class Game():
    def __init__(self, row=4, col=4, initial=2):
        self.game = Grid(row, col, initial)
        self.play()


    def printPrompt(self):
        if sys.platform == 'win32':
            os.system("cls")
        else:
            os.system("clear")
        print('Press "w", "a", "s", or "d" to move Up, Left, Down or Right respectively.')
        print('Enter "p" to quit.\n')
        self.game.drawGrid()
        print('\nScore: ' + str(self.game.score))


    def play(self):

        moves = {'w' : 'Up',
                 'a' : 'Left',
                 's' : 'Down',
                 'd' : 'Right'}

        stop = False
        collapsible = True

        while not stop and collapsible:
            self.printPrompt()
            key = input('\nEnter a move: ')

            while not key in list(moves.keys()) + ['p']:
                self.printPrompt()
                key = input('\nEnter a move: ')

            if key == 'p':
                stop = True
            else:
                move = getattr(self.game, 'collapse' + moves[key])
                collapsed = move()

                if collapsed:
                    self.game.updateEmptiesSet()
                    self.game.assignRandCell()

                collapsible = self.game.collapsible()

        if not collapsible:
            if sys.platform == 'win32':
                os.system("cls")
            else:
                os.system("clear")
            print()
            self.game.drawGrid()
            print('\nScore: ' + str(self.game.score))
            print('No more legal moves.')


if __name__ == '__main__':
    game = Game(5,5)
    grid = Grid()
    
