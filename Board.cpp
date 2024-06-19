#include "Board.h"

// Constructor
Board::Board(int size, std::vector<Node>& vect, const std::string file_path) 
{

    this->w = size;
    this->h = size;
    this->s = size * size;

    player = 'B';
    moves = parseSGF(file_path);

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

void Board::handle_mouse_click(const SDL_Event& e, char* player, int cycle) 
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
                cycle = cycle + 1;
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


int Board::add_move(int x, int y, char player)
{
    int index = get_index(x, y);
    nodes[index].set_index(index);
    if (nodes[index].get_player() == '.')
    {
        nodes[index].set_player(player);
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

bool Board::get_up_to_date()
{
    return (move_count == cycle);
}

void Board::build_dfs(const int index)
{

    if (nodes[index].get_player() == '.') return;
    if (nodes[index].get_visited()) return;

    int x = index / w;
    int y = index % h;

    Node* node = (&nodes[index]);
    node->set_visited(true);

    // check seperaly for out of bounds
    
    //up
    if (y >= 0) 
    {
        Node* node_up;
        int index_up = index - w;
        node_up = (&nodes[index_up]);

        if (node_up->get_player() == node->get_player())
        {
            node->add_child(node_up, 0);
            node_up->add_parent(node);
            build_dfs(index_up);
        }
    }

    //Down
    if (y < h - 1) 
    {
        Node* node_down;
        int index_down = index + w;
        node_down = (&nodes[index_down]);

        if (node_down->get_player() == node->get_player())
        {
            node->add_child(node_down, 2);
            node_down->add_parent(node);
            build_dfs(index_down);
        }
    }

    //Left 
    if (x >= 0)
    {
        Node* node_left;
        int index_left = index - 1;
        node_left = (&nodes[index_left]);

        if (node_left->get_player() == node->get_player()) 
        {
            node->add_child(node_left, 3);
            node_left->add_parent(node);
            build_dfs(index_left);
        }
    }

    //Right
    if(x < w - 1)
    {
        Node* node_right;
        int index_right = index + 1;
        node_right = (&nodes[index_right]);

        if (node_right->get_player() == node->get_player())
        {
            node->add_child(node_right, 1);
            node_right->add_parent(node);
            build_dfs(index_right);
        }
    }
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

void Board::reset()
{
    for (int i = 0; i < nodes.size(); i++)
    {
        nodes[i].set_player('.');
    }
}

void Board::print()
{   
    std::cout << "board" << std::endl;
    std::cout << "_01234678" << std::endl;
    for (int i = 0; i < h; i++)
    {
        std::cout<<i;
        for (int j = 0; j < w; j++)
        {
            char player = nodes[get_index(j ,i)].get_player();

            std::cout << player;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void Board::update_heads()
{
    heads.resize(0);
    reset_visited();

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
    std::cout << "move_count: " << move_count << ", cycle: "<< cycle << std::endl; 
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
            reset();
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

/**
 * Prints all children of a node.
 *
 * @param node this will be viewed the head.
 * @return a vector aof all children an childrens children.
 */
std::vector<Node*> Board::get_group(Node* head)
{

    std::vector<Node*> nodes;

    reset_visited();

    dfs_group(head, &nodes);

    return nodes;
}

void Board::dfs_group(Node *head, std::vector<Node *> *nodes)
{
    if (head->get_visited()) return;

    head->set_visited(true);

    nodes->push_back(head);

    for (int i = 0; i < 4; i++)
    {
        Node* child = head->get_child(i);
        if (!(child == nullptr))
        {
            dfs_group(child, nodes);
        }
    }
}


void Board::print_heads()
{
    std::cout << "heads:"<<std::endl;
    for ( auto h : heads) 
    {
        int index = h->get_index();
        std::cout << "(" << get_x(index) << ";" << get_y(index) << ")"<< std::endl;
    }
    std::cout << std::endl;
}

void Board::print_groups()
{
    std::cout << "groups:" << std::endl;
    reset_visited();
    for(int k = 0; k < nodes.size(); k++ )
    {
        if (!(nodes[k].get_player() == '.') && !(nodes[k].get_visited()))
        {
            std::vector<Node*> vect = get_group(&nodes[k]);

            std::cout << "Printing " << "(" <<get_x(k)<< "; " << get_y(k) << ")"  << "-tree, colour: " << nodes[k].get_player()<<std::endl;

            for (int l = 0; l < vect.size(); l++) 
            {
                std::cout << "(" <<get_x(vect[l]->get_index())<< "; " << get_y(vect[l]->get_index()) << ")" << std::endl;
            }
        }
    }
}

void Board::print_coords(int index)
{

    std::cout << "coords: (" << get_x(index) << ";" << get_y(index) << ")" << std::endl; 
}

void Board::update_cycle(char player)
{

    update_groups();
    update_liberties();
    update_heads();

    if (player == 'W') {player = 'B';}
    else {player = 'W';}

    update_life(player);

    if (player == 'W') {player = 'B';}
    else {player = 'W';}

    update_groups();
    update_liberties();
    update_heads();

    update_life (player);

}

void Board::update_groups()
{
    reset_children();
    reset_parent();

        for (int i = 0; i < nodes.size(); i++)
        {
            reset_visited();
            build_dfs(i);
        }


}

void Board::update_liberties()
{
    for(int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            int l = get_liberties(j, i);
            int index = get_index(j, i);
            nodes[index].set_liberties(l);
        }
    }
}

void Board::update_life(char player)
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

        if (!life && head->get_player() == player) 
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

std::vector<std::pair<int, int>> Board::parseSGF(const std::string& filePath) {
    std::vector<std::pair<int, int>> moves;

    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Failed to open SGF file: " << filePath << std::endl;
        return moves;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("SZ[") != std::string::npos) {
            int startPos = line.find("SZ[") + 3;
            int endPos = line.find("]", startPos);
            int boardSize = std::stoi(line.substr(startPos, endPos - startPos));
            std::cout << "Board Size: " << boardSize << std::endl;
        } else if (line.find("KM[") != std::string::npos) {
            int startPos = line.find("KM[") + 3;
            int endPos = line.find("]", startPos);
            float komi = std::stof(line.substr(startPos, endPos - startPos));
            std::cout << "Komi: " << komi << std::endl;
        } else if (line.find("RU[") != std::string::npos) {
            int startPos = line.find("RU[") + 3;
            int endPos = line.find("]", startPos);
            std::string ruleset = line.substr(startPos, endPos - startPos);
            std::cout << "Ruleset: " << ruleset << std::endl;
        } else if (line.find("RE[") != std::string::npos) {
            int startPos = line.find("RE[") + 3;
            int endPos = line.find("]", startPos);
            std::string result = line.substr(startPos, endPos - startPos);
            std::cout << "Result: " << result << std::endl;
        } else if (line.find("PB[") != std::string::npos) {
            int startPos = line.find("PB[") + 3;
            int endPos = line.find("]", startPos);
            std::string blackPlayer = line.substr(startPos, endPos - startPos);
            std::cout << "Black Player: " << blackPlayer << std::endl;
        } else if (line.find("PW[") != std::string::npos) {
            int startPos = line.find("PW[") + 3;
            int endPos = line.find("]", startPos);
            std::string whitePlayer = line.substr(startPos, endPos - startPos);
            std::cout << "White Player: " << whitePlayer << std::endl;
        } else if (line.find(";B[") != std::string::npos || line.find(";W[") != std::string::npos) {
            size_t pos = 0;
            while ((pos = line.find(";")) != std::string::npos) {
                std::string move = line.substr(pos + 1, 5); // Expecting format like "B[ab]"
                line.erase(0, pos + 6); // Erase up to the next move

                if (move.size() >= 4 && (move[0] == 'B' || move[0] == 'W')) {
                    char player = move[0];
                    char x = move[2];
                    char y = move[3];
                    if (x == ']' || y == ']') {
                        // Pass move
                        moves.push_back({-1, -1});
                    } else {
                        moves.push_back({x - 'a', y - 'a'});
                    }
                }
            }
        }
    }
    return moves;
}