package com.example.ky;

/**
 * The GameBoard class is the "brains" of this program. It maintains the state
 * of the gameboard, handles moves, and decides who wins. The only thing it
 * does NOT do is handle user input/output. That part is handled by the Main class.
 * @author draperg
 *
 */
public class KyGameBoard {

    /**
     * grid is a two-dimensional (5x5) array representing the actual gameboard
     */
    private KyPlayer[][] grid;

    /**
     * DIM is set to 5. Change this if you want a bigger/smaller gameboard.
     * The "true" Slide game uses a 5x5 board.
     */
    private final int DIM = 5;

    /**
     * keeps track of whose turn it is (either Player.X or Player.O)
     */
    private KyPlayer currentPlayer;

    /**
     * Constructor for our GameBoard class. Initializes the gameboard to blank.
     * Arbitrarily sets X as the first player. I guess you could change it to O
     * if you want. Or better yet, make it random.
     */
    public KyGameBoard() {
        grid = new KyPlayer[DIM][DIM];
        clear();
        currentPlayer = KyPlayer.X;
    }

    /**
     * Just "blanks out" the gameboard.
     */
    public void clear() {
        for (int i=0; i<DIM; i++) {
            for (int j=0; j<DIM; j++) {
                grid[i][j] = KyPlayer.BLANK;
            }
        }
    }

    /**
     * This method processes a single move for the current player. The input parameter is the row or column the user selected.
     * Tokens are "inserted" into the top of the grid (for vertical moves) or into the left side (for horizontal moves).
     * Tokens move from top to bottom (for vertical moves) or from left to right (for horizontal moves).
     * Existing tokens slide down (or right) to make way for the new tokens. If a column is full, the bottommost token
     * is removed. If a row is full, the rightmost token is removed.
     * At the conclusion of a move, the currentPlayer variable is toggled (X to O, or O to X).
     * @param move one of the characters '1', '2', '3', '4', '5' (for vertical moves) or 'A', 'B', 'C', 'D', 'E' (for horizontal moves). Any other values will result in buggy results.
     */
    public void submitMove(char move) {
        if (move >= '1' && move <= '5') {
            //vertical move, move stuff down
            int col = Integer.parseInt(""+move)-1;
            KyPlayer newVal = currentPlayer;
            for (int i=0; i<DIM; i++) {
                if (grid[i][col] == KyPlayer.BLANK) {
                    grid[i][col] = newVal;
                    break;
                } else {
                    KyPlayer tmp = grid[i][col];
                    grid[i][col] = newVal;
                    newVal = tmp;
                }
            }

        } else { //A-E
            //horizontal move, move stuff right
            int row = (int)(move - 'A');
            KyPlayer newVal = currentPlayer;
            for (int i=0; i<DIM; i++) {
                if (grid[row][i] == KyPlayer.BLANK) {
                    grid[row][i] = newVal;
                    break;
                } else {
                    KyPlayer tmp = grid[row][i];
                    grid[row][i] = newVal;
                    newVal = tmp;
                }
            }
        }
        if (currentPlayer == KyPlayer.X) {
            currentPlayer = KyPlayer.O;
        } else {
            currentPlayer = KyPlayer.X;
        }
    }

    /**
     * Checks all rows, columns and the two diagonals for five matching tokens in a row.
     * I'll explain the logic for rows. The logic for columns and diagonals are analogous.
     * For each of the five rows, check the value of the leftmost element. If it's not blank,
     * loop through the remaining four elements to see if they match the first one. If
     * they do, stop and declare that player the winner. But if any does not match the
     * first one, skip that row and search the next row for matches in the same manner.
     * @return the value of the winning player, X or O or TIE. Returns BLANK if no one has yet won (the most common state).
     */
    public KyPlayer checkForWin() {
        KyPlayer winner = KyPlayer.BLANK;
        KyPlayer tmpWinner;

        //check all rows
        for (int i=0; i<DIM; ++i) {
            if (grid[i][0] != KyPlayer.BLANK) {
                tmpWinner = grid[i][0];
                for (int j=0; j<DIM; ++j) {
                    if (grid[i][j] != tmpWinner) {
                        tmpWinner = KyPlayer.BLANK;
                        break;
                    }
                }
                if (tmpWinner != KyPlayer.BLANK) {
                    if (winner == KyPlayer.BLANK) {
                        winner = tmpWinner;
                    } else {
                        return KyPlayer.TIE;
                    }
                }
            }
        }

        //check all columns
        tmpWinner = KyPlayer.BLANK;
        for (int i=0; i<DIM; ++i) {
            if (grid[0][i] != KyPlayer.BLANK) {
                tmpWinner = grid[0][i];
                for (int j=0; j<DIM; ++j) {
                    if (grid[j][i] != tmpWinner) {
                        tmpWinner = KyPlayer.BLANK;
                        break;
                    }
                }
                if (tmpWinner != KyPlayer.BLANK) {
                    if (winner == KyPlayer.BLANK) {
                        winner = tmpWinner;
                    } else {
                        return KyPlayer.TIE;
                    }
                }
            }
        }

        //at this point, either there's a tie, or there's not.
        //You can't have a tie with diagonals.
        if (winner != KyPlayer.BLANK) {
            return winner;
        }

        //check top-left -> bottom-right diagonal
        if (grid[0][0] != KyPlayer.BLANK) {
            winner = grid[0][0];
            for (int i=0; i<DIM; ++i) {
                if (grid[i][i] != winner) {
                    winner = KyPlayer.BLANK;
                    break;
                }
            }
            if (winner != KyPlayer.BLANK) {
                return winner; //5 in a diagonal!
            }
        }

        //check bottom-left -> top-right diagonal
        if (grid[DIM-1][0] != KyPlayer.BLANK) {
            winner = grid[DIM-1][0];
            for (int i=0; i<DIM; ++i) {
                if (grid[DIM-1-i][i] != winner) {
                    winner = KyPlayer.BLANK;
                    break;
                }
            }
            if (winner != KyPlayer.BLANK) {
                return winner; //5 in a diagonal!
            }
        }

        return winner;
    }

    /**
     * returns the value of the current player (X or O).
     * @return
     */
    public KyPlayer getCurrentPlayer() {
        return currentPlayer;
    }
}
