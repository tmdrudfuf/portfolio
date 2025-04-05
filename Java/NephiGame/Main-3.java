import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.Graphics;
import java.awt.Color;
import java.util.ArrayList;
import java.util.List; // Import List
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JOptionPane;  // Import JOptionPane
import java.util.Random; // Import Random

public class Main extends JPanel implements KeyListener {
    public static final int CELL_SIZE = 50;

    private List<Tree> trees; // Change to List<Tree>
    private List<Sprite> sprites; // New list for all sprites
    private int numRows;
    private int numCols;
    private boolean showMessage = true; // Flag to control JOptionPane

    public Main() {
        trees = new ArrayList<>();
        sprites = new ArrayList<>(); // Instantiate sprites as an ArrayList
        numRows = 9;
        numCols = 9;
        createTrees();
        createSprites();

        // Add KeyListener to the JPanel
        addKeyListener(this);
        // Request focus for KeyListener to work
        setFocusable(true);
        requestFocusInWindow();
    }

    private void createTrees() {
        trees.clear();
        // Arrange the location for each tree
        int[][] treePositions = {
                {4, 0}, {2, 1}, {5, 1}, {8, 2}, {3, 3}, {1, 4}, {8, 4}, {3, 5}, {6, 5}, {6, 8}
        };
        for (int i = 0; i < 10; i++) {
            int x = treePositions[i][0];
            int y = treePositions[i][1];
            Tree tree = new Tree(x, y);
            trees.add(tree);
            sprites.add(tree); // Add to sprites list
        }
    }

    private void createSprites() {
        // Instantiate each sprite object and add it to the sprites list
        sprites.add(new Nephi(1, 1));
        sprites.add(new Bow(2, 2));
        sprites.add(new Arrow(3, 6));
        sprites.add(new Beast(4, 4));
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        setBackground(Color.LIGHT_GRAY);
        g.setColor(Color.BLACK);
        g.drawRect(0, 0, numCols * CELL_SIZE, numRows * CELL_SIZE);

        // Draw all sprites in the sprites list
        for (Sprite sprite : sprites) {
            sprite.draw(g);
        }
    }

    @Override
    public void keyPressed(KeyEvent e) {
        int keyCode = e.getKeyCode();
        Nephi nephi = null;
        Beast beast = null;

        // Find Nephi and Beast in the sprites list
        for (Sprite sprite : sprites) {
            if (sprite instanceof Nephi) {
                nephi = (Nephi) sprite;
            } else if (sprite instanceof Beast) {
                beast = (Beast) sprite;
            }
        }

        // Check if Nephi overlaps with Bow or Arrow when the 'S', 'D', 'A', or 'W' key is pressed
        for (Sprite sprite : sprites) {
            if (sprite instanceof Bow && nephi.getLocation().equals(sprite.getLocation())) {
                nephi.pickUpBow();
                sprites.remove(sprite);
                break; // Exit the loop after picking up one bow
            } else if (sprite instanceof Arrow && nephi.getLocation().equals(sprite.getLocation())) {
                nephi.pickUpArrow();
                sprites.remove(sprite);
                break; // Exit the loop after picking up one arrow
            }
        }

        // Shooting logic
        if (nephi != null && beast != null) {
            shoot(keyCode, nephi, beast);
        }

        // Move Nephi logic
        Point currentNephiPos = nephi.getLocation();
        Point nextNephiPos = new Point(currentNephiPos);

        switch (keyCode) {
            // Nephi movement with arrow keys
            case KeyEvent.VK_UP:
                if (currentNephiPos.y > 0) {
                    nextNephiPos.y--;
                }
                break;
            case KeyEvent.VK_DOWN:
                if (currentNephiPos.y < numRows - 1) {
                    nextNephiPos.y++;
                }
                break;
            case KeyEvent.VK_LEFT:
                if (currentNephiPos.x > 0) {
                    nextNephiPos.x--;
                }
                break;
            case KeyEvent.VK_RIGHT:
                if (currentNephiPos.x < numCols - 1) {
                    nextNephiPos.x++;
                }
                break;
        }

        // Check if the next position is not occupied by trees
        boolean canMoveNephi = checkCollision(nextNephiPos, trees);

        // Update Nephi's position if it can move
        if (canMoveNephi) {
            nephi.setLocation(nextNephiPos);
        }

        // Repaint the panel
        repaint();
    }

    @Override
    public void keyReleased(KeyEvent e) {
        // Stub method (not needed for this program)
    }

    @Override
    public void keyTyped(KeyEvent e) {
        // Stub method (not needed for this program)
    }

    // Method to check collision with trees
    private boolean checkCollision(Point position, List<Tree> trees) {
        for (Tree tree : trees) {
            if (tree.getLocation().equals(position)) {
                return false; // Collision detected, cannot move
            }
        }
        return true; // No collision, can move
    }

    // Method to handle shooting logic
    private void shoot(int keyCode, Nephi nephi, Beast beast) {
        // Shooting logic as provided before
        boolean hit = false;

        switch (keyCode) {
            case KeyEvent.VK_W:
                hit = nephi.getLocation().x == beast.getLocation().x &&
                        nephi.getLocation().y > beast.getLocation().y;
                break;
            case KeyEvent.VK_S:
                hit = nephi.getLocation().x == beast.getLocation().x &&
                        nephi.getLocation().y < beast.getLocation().y;
                break;
            case KeyEvent.VK_A:
                hit = nephi.getLocation().y == beast.getLocation().y &&
                        nephi.getLocation().x > beast.getLocation().x;
                break;
            case KeyEvent.VK_D:
                hit = nephi.getLocation().y == beast.getLocation().y &&
                        nephi.getLocation().x < beast.getLocation().x;
                break;
        }

        if (hit && showMessage) {
            showMessage = false; // Set flag to false to avoid repeated messages
            JOptionPane.showMessageDialog(this, "Congratulations! You slayed the beast!");
            // Move the beast to a random unoccupied cell
            moveBeastRandomly(beast);
        } else if (!hit) {
            showMessage = true; // Reset flag if Nephi misses
        }
    }

    // Method to move the beast to a random unoccupied cell
    private void moveBeastRandomly(Beast beast) {
        Random random = new Random();

        do {
            int newX = random.nextInt(numCols);
            int newY = random.nextInt(numRows);
            beast.setLocation(new Point(newX, newY));
        } while (!checkCollision(beast.getLocation(), trees));
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Nephi Game");
        frame.add(new Main());
        frame.setSize(600, 600);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }
}
