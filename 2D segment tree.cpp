class NumMatrix {
public:
    class SegmentTreeNode2D{
    public:
        int x1, y1;
        int x2, y2;
        SegmentTreeNode2D* left;
        SegmentTreeNode2D* right;
        SegmentTreeNode2D* up;
        SegmentTreeNode2D* down;
        int sum;
        SegmentTreeNode2D(int x1, int y1, int x2, int y2){
            this->x1 = x1;
            this->y1 = y1;
            this->x2 = x2;
            this->y2 = y2;
            this->left = NULL;
            this->right = NULL;
            this->up = NULL;
            this->down = NULL;
            this->sum = 0;
        }
    };
    SegmentTreeNode2D* build(vector<vector<int>>& matrix, int x1, int y1, int x2, int y2){
        if(x1>x2||y1>y2){
            return NULL;
        }
        if(x1==x2&&y1==y2){
            SegmentTreeNode2D* current = new SegmentTreeNode2D(x1,y1,x2,y2);
            current->sum = matrix[x1][y1];
            return current;
        }
        SegmentTreeNode2D* current = new SegmentTreeNode2D(x1, y1, x2, y2);
        int midX = x1+(x2-x1)/2;
        int midY = y1+(y2-y1)/2;
        current->left = build(matrix, x1, y1, midX, midY);
        current->right = build(matrix, x1, midY+1, midX, y2);
        current->up = build(matrix, midX+1, y1, x2, midY);
        current->down = build(matrix, midX+1, midY+1, x2, y2);
        current->sum = (current->left?current->left->sum:0)+(current->right?current->right->sum:0)+(current->up?current->up->sum:0)+(current->down?current->down->sum:0);
        return current;
    }
    void modify(SegmentTreeNode2D* root, int x, int y, int& value){
        if(root==NULL)
            return ;
        if(root->x1==root->x2&&root->y1==root->y2){
            if(root->x1==x&&root->y1==y){
                root->sum = value;
                return ;
            }
        }
        int midX = root->x1+(root->x2-root->x1)/2;
        int midY = root->y1+(root->y2-root->y1)/2;
        if(x<=midX&&y<=midY){
            modify(root->left, x, y, value);
        }else if(x>=(midX+1)&&y>=(midY+1)){
            modify(root->down, x, y, value);
        }else if(x>=(midX+1)&&x<=root->x2&&y>=y&&y<=midY){
            modify(root->up, x, y, value);
        }else{
            modify(root->right, x, y, value);
        }
        root->sum = (root->left?root->left->sum:0)+(root->right?root->right->sum:0)+(root->up?root->up->sum:0)+(root->down?root->down->sum:0);
        return ;
    }
    
    int search(SegmentTreeNode2D* root, int x1, int y1, int x2, int y2){
        if(root==NULL)
            return 0;
        if(root->x1==x1&&root->y1==y1&&root->x2==x2&&root->y2==y2){
            return root->sum;
        }
        int midX = root->x1+(root->x2-root->x1)/2;
        int midY = root->y1+(root->y2-root->y1)/2;
        int result = 0;
        
        if(x1<=midX&&y1<=midY)
            result+= search(root->left, x1, y1, min(midX,x2), min(midY,y2));
        if(x1<=midX&&y2>midY)
            result+= search(root->right, x1, max(midY+1, y1), min(x2, midX), y2);
        if(x2>midX&&y2>midY)
            result+= search(root->down, max(x1, midX+1), max(y1, midY+1), x2, y2);
        if(x2>midX&&y1<=midY)
            result+= search(root->up, max(x1, midX+1), y1, x2, min(y2, midY));
        
        return result;
    }
    
    NumMatrix(vector<vector<int>> matrix) {
        if(matrix.size()==0)
            return ;
        root = build(matrix, 0, 0, matrix.size()-1, matrix[0].size()-1);
    }
    
    void update(int row, int col, int val) {
        if(root)
            modify(root, row, col, val);
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        if(root)
            return search(root, row1, col1, row2, col2);
        else
            return -1;
    }
    
private:
    SegmentTreeNode2D* root;
};
