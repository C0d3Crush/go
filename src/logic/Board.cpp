#include "logic/Board.h"
#include "Board.h"

// Constructor
Board::Board(int size, std::vector<Node>& vect)
{
    this->w = size;
    this->h = size;
    this->s = size * size;



    player = 'B';
    moves = {
        {0,0}, {0,1}, 
        {1,0}, {4,4}, 
        {2,0}, {4,5}, 
        {3,4}, {2,4}, 
        {1,4}, {0,4}, 
        {0,3}, {0,2}, 
        {0,8}, {3,0},
        {1,8}, {2,1},
        {2,8}, {1,1},
        {4,8}, {8,1}
    };

    cycle = moves.size();


    nodes = vect;
    nodes.resize(size * size);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++) 
        {
            int index = get_index(j, i);
            nodes[index].set_player('.');    
            nodes[index].set_index(index);
        }
    }
}

// Destructor
Board::~Board() {}

void Board::draw(SDL_Renderer *renderer)
{
    draw_board(renderer);
    draw_stones(renderer);
}

void Board::draw_stones(SDL_Renderer *renderer)
{

    int cellSize = (WINDOW_WIDTH - 2 * BOARD_MARGIN) / (w - 1);
    int radius = cellSize / 2;

    for (int i = 0; i < s; i++)
    {
        Node* node = &nodes[i];//get_node(i);

        if (node->get_player() == '.') continue;

        int x = cellSize * (get_x(i)) + BOARD_MARGIN;
        int y = cellSize * (get_y(i)) + BOARD_MARGIN;

        //std::cout<<"test:"<<"x: "<<x<<" y: "<<y<<std::endl;
        if (node->get_player() == 'B') 
        { 
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        } 
        else 
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        draw_square(renderer, x, y, radius);
    }
}

void Board::draw_square(SDL_Renderer *renderer, int centerX, int centerY, int radius)
{

    int squareSize = radius * 2; // Square size is double the radius

    // Calculate the coordinates of the square's top-left corner
    int startX = centerX - (squareSize / 2);
    int startY = centerY - (squareSize / 2);

    // Draw the square
    SDL_Rect squareRect = { startX, startY, squareSize, squareSize };
    SDL_RenderFillRect(renderer, &squareRect);
}

void Board::draw_board(SDL_Renderer *renderer)
{
    //int boardSize = s;

    int cellSize = (WINDOW_WIDTH - 2 * BOARD_MARGIN) / (w - 1);
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    for (int i = 0; i < w; ++i) 
    {
        SDL_RenderDrawLine
        (
            renderer, 
            BOARD_MARGIN, 
            BOARD_MARGIN + i * cellSize, 
            WINDOW_WIDTH - BOARD_MARGIN, 
            BOARD_MARGIN + i * cellSize
        );
        SDL_RenderDrawLine
        (
            renderer, 
            BOARD_MARGIN + i * cellSize, 
            BOARD_MARGIN, 
            BOARD_MARGIN + i * cellSize, 
            WINDOW_WIDTH - BOARD_MARGIN
        );
    }
}

void Board::handle_mouse_click(const SDL_Event& e, char* player) 
{
    std::cout << ">>===== Handle Mouse =====<<" << std::endl;
    if (e.button.button == SDL_BUTTON_LEFT) 
    {
        // Capture raw mouse coordinates
        int mouseX = e.button.x;
        int mouseY = e.button.y;

        // Calculate cell size
        int boardWidth = width();
        int boardHeight = height();
        int cellSize = (WINDOW_WIDTH - BOARD_MARGIN * 2) / boardWidth;

        // Adjust mouse coordinates by subtracting the board's margin
        int adjustedMouseX = mouseX - BOARD_MARGIN;
        int adjustedMouseY = mouseY - BOARD_MARGIN;

        // Ensure adjusted coordinates are within valid range
        if (adjustedMouseX < 0 || adjustedMouseX >= (boardWidth * cellSize) || 
            adjustedMouseY < 0 || adjustedMouseY >= (boardHeight * cellSize)) {
            std::cout << "Mouse coordinates out of board bounds!" << std::endl;
            return;
        }

        // Convert adjusted mouse coordinates to grid coordinates with rounding
        int gridX = adjustedMouseX / cellSize;
        int gridY = adjustedMouseY / cellSize;

        // Ensure grid coordinates are within board dimensions
        if (gridX >= boardWidth) gridX = boardWidth - 1;
        if (gridY >= boardHeight) gridY = boardHeight - 1;

        // Ensure the calculated grid position is within the board limits
        if (gridX >= 0 && gridX < size() && gridY >= 0 && gridY < size()) 
        {
            int index = get_index(gridX, gridY);

            std::cout << "index: " <<index << " player at coords: " << nodes[index].get_player() << std::endl;
            
            std::cout << "(" << gridX << "; " << gridY << ")" << std::endl;

            std::cout << "(" << get_x(index) << "; "<< get_y(index) << ")"<< std::endl;

            if (nodes[index].get_player() == '.') 
            {
                std::cout << cycle << std::endl;
                cycle++;
                moves.push_back({gridX, gridY});
            }
            else std::cout << "Cant place there. Space is ocupied." << std::endl;
        }
        else
        {
            std::cout << "Click out of board boundaries!" << std::endl;
        }
    }
}

int Board::get_index(int x, int y)
{
    return (y * h) + x;
}

int Board::get_x(int index)
{
    return index % w;
}


int Board::get_y(int index)
{
    return index / h;
}


int Board::size()
{
    return s;
}

int Board::width()
{
    return w;
}

int Board::height()
{
    return h;
}


int Board::add_move(int x, int y, char p)
{
    int index = get_index(x, y);
    nodes[index].set_index(index);
    if (nodes[index].get_player() == '.')
    {
        nodes[index].set_player(p);
        return 0;
    }
    else 
    {
        return 1;
    }
}

int Board::get_liberties(int x, int y)
{
    int count = 0;
    int index = get_index(x, y);
    //up
    if (y > 0) 
    {
        if (nodes[get_index(x, y - 1)].get_player() == '.') 
            count++;
    }
    //Down
    if (y < h - 1) 
    {
        if (nodes[get_index(x, y + 1)].get_player() == '.') 
            count++;
    }

    //Left 
    if (x > 0)
    {
        if (nodes[get_index(x - 1, y)].get_player() == '.') 
            count++;
    }

    //Right
    if(x < w - 1)
    {
       if (nodes[get_index(x + 1, y)].get_player() == '.') 
        count++;
    }    
    return count;
}

int Board::get_moves_size()
{
    return moves.size();
}

int Board::get_cycle()
{
    return cycle;
}

bool Board::get_up_to_date()
{
    return (move_count == cycle);
}
bool Board::build_dfs(const int index)
{
    int child_count = 0;
    if (nodes[index].get_player() == '.') return 0;
    if (nodes[index].get_visited()) return 0;

    int x = get_x(index);  // Changed from w to index
    int y = get_y(index);  // Changed from h to index

    Node* node = (&nodes[index]);
    node->set_visited(true);

    // check separately for out of bounds

    // Up
    if (y > 0) 
    {
        int index_up = index - w;
        Node* node_up = (&nodes[index_up]);

        if (node_up->get_player() == node->get_player())
        {
            if (build_dfs(index_up))
            {
                node->add_child(node_up, 0);
                node_up->add_parent(node);
                child_count++;
            }
        }
    }

    // Down
    if (y < h - 1) 
    {
        int index_down = index + w;
        Node* node_down = (&nodes[index_down]);

        if (node_down->get_player() == node->get_player())
        {
            if (build_dfs(index_down))
            {
                node->add_child(node_down, 2);
                node_down->add_parent(node);
                child_count++;
            }
        }
    }

    // Left 
    if (x > 0)
    {
        int index_left = index - 1;
        Node* node_left = (&nodes[index_left]);

        if (node_left->get_player() == node->get_player()) 
        {
            if (build_dfs(index_left))
            {
                node->add_child(node_left, 3);
                node_left->add_parent(node);
                child_count++;
            }
        }
    }

    // Right
    if (x < w - 1)
    {
        int index_right = index + 1;
        Node* node_right = (&nodes[index_right]);

        if (node_right->get_player() == node->get_player())
        {
            if (build_dfs(index_right))
            {
                node->add_child(node_right, 1);
                node_right->add_parent(node);
                child_count++;
            }
        }
    }

    return 1;
}

bool Board::dfs_life(Node *head)
{
    
    if(head->get_liberties() != 0)
    {
        return 1;
    }
    for (int i = 0; i < 4; i++)
    {
        Node* child = head->get_child(i);
        if (!(child == nullptr))
        {
            return find_life(child);
        }
    }

    return 0;
}

void Board::reset_visited()
{
    for (int i = 0; i < nodes.size(); i++) 
    {
        nodes[i].set_visited(false);
    }
}

void Board::reset_tree()
{
    reset_children();
    reset_parent();
}

void Board::reset_children() 
{
    for (int i = 0; i < nodes.size(); i++) 
    {
        nodes[i].add_child(nullptr, 0);
        nodes[i].add_child(nullptr, 1);
        nodes[i].add_child(nullptr, 2);
        nodes[i].add_child(nullptr, 3);
    }
}

void Board::reset_parent()
{
    for (int i = 0; i < nodes.size(); i++) 
    {
        nodes[i].add_parent(nullptr);
    }
}

void Board::reset_stones()
{
    for (int i = 0; i < nodes.size(); i++)
    {
        nodes[i].set_player('.');
    }
}

void Board::print()
{   
    std::cout << "board" << std::endl;
    std::cout << "_012345678" << std::endl;
    for (int i = 0; i < h; i++)
    {
        std::cout<<i;
        for (int j = 0; j < w; j++)
        {
            char p = nodes[get_index(j ,i)].get_player();

            std::cout << p;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void Board::update_heads()
{
    heads.resize(0);
    //reset_visited();

    for(int k = 0; k < nodes.size(); k++ )
    {
        if (!(nodes[k].get_player() == '.') && !(nodes[k].get_visited()))
        {
            //bool alive = false;
            std::vector<Node*> vect = get_group(&nodes[k]);
            heads.push_back(&nodes[k]);
        }
    }
}

bool Board::update()
{   
    //std::cout << "move_count: " << move_count << ", cycle: "<< cycle << std::endl; 
    if (move_count < cycle)
        {
            int x = moves[move_count].first;
            int y = moves[move_count].second;    
        
            if (add_move(moves[move_count].first, moves[move_count].second, player)) 
            {
                std::cerr << "Error: bad move" << std::endl;
            }
            else
            {
                if(player == 'W') player = 'B';
                else player = 'W';    
            }
            update_cycle(player);     
            move_count++;
            return true;
        }
        else if (cycle < move_count)
        {
            reset_stones();
            player = 'B';

            for (move_count = 0; move_count < cycle; move_count++)
            {
                int x = moves[move_count].first;
                int y = moves[move_count].second;    
            
                if (add_move(moves[move_count].first, moves[move_count].second, player)) 
                {
                    std::cerr << "Error: bad move" << std::endl;
                }
                else
                {
                    if(player == 'W') player = 'B';
                    else player = 'W';    
                }
                update_cycle(player);     
            }
            return true;
        }
        if (cycle == move_count)
        {
            //std::cout << "up to date" << std::endl;
            //print();
            return false;
        } 
}

void Board::set_cycle(int c)
{
    cycle = c;
}

std::vector<Node*> Board::get_group(Node* head)
{
    std::vector<Node*> nodes;
    reset_visited();
    dfs_group(head, &nodes);

    return nodes;
}
/**
 * @brief IMPORTANT: If this function return false it means this head has no children
 *  
 * this behaiviour could be usefull to check if a ko happend?
 */
bool Board::dfs_group(Node *head, std::vector<Node *> *nodes)
{
    if (head->get_visited()) return 0;

    head->set_visited(true);
    nodes->push_back(head);

    for (int i = 0; i < 4; i++)
    {
        Node* child = head->get_child(i);
        if (!(child == nullptr))
        {
            if (dfs_group(child, nodes))
            {

            }
        }
    }
}

void Board::print_heads()
{
    std::cout << "Tree:" << std::endl;
    for (Node* head : heads) {
        head->print_tree();
    }
}

void Board::print_groups()
{
    std::cout << "Groups:" << std::endl;
    
    for (auto h : heads)
    {
        std::cout << "head: " << h->get_player() << " ";
        print_coords(h->get_index());

        std::vector<Node*>group = get_group(h); 
        for (int i = 0; i < group.size(); i++)
        {
            std::cout << "stone["<<i<<"]: " << group[i]->get_player()<< " ";
            print_coords(group[i]->get_index());
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Board::print_coords(int index)
{
    std::cout << "Coords: (" << get_x(index) << ", " << get_y(index) << ")" << std::endl; 
}



void Board::update_cycle(char p)
{
    for (int i = 0; i < 2; i++)
    {
        if (p == 'W') {p = 'B';}
        else {p = 'W';}

        update_trees();

        for(int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                update_liberties(x, y);
            }
        }    
        
        update_heads();
        update_life(p);
    }
}
void Board::update_trees()
{
    reset_tree();
    for (int i = 0; i < nodes.size(); i++)
    {
        reset_visited();
        build_dfs(i);
    }
}
void Board::update_liberties(int x, int y)
{
    int liberties = get_liberties(x, y);
    int index = get_index(x, y);
    nodes[index].set_liberties(liberties);
}
void Board::update_life(char p)
{
    for (auto head : heads)
    {
        std::vector<Node*> group = get_group(head);
        std::vector<int> liberties_update;

        bool life = false;

        for (auto e : group)
        {
            liberties_update.push_back(e->get_liberties());
        }

        for (auto e : liberties_update)
        {
            if (e == 0) continue;

            else life = true;
        }

        if (!life && head->get_player() == p) 
        {
            remove_stones(head); 
        }
    }
}

bool Board::find_life(Node *head)
{
    if (head->get_visited()) return head->get_liberties();
    
    bool value = dfs_life(head);

    reset_visited();

    return value;
}

int Board::remove_stones(Node *head)
{
    std::vector<Node*> dead_stones = get_group(head);

    for (int i = 0; i < dead_stones.size(); i++) 
    {
        //std::cout << "deleting node idx: " << i<< std::endl;
        dead_stones[i]->set_player('.'); 
    }

    return dead_stones.size();
}