struct Entity{
    b32 enabled = 1;

    Vector2 pos;
    float rotation;
    
    virtual void init(){}
    virtual void born(){}
    
    virtual void update(){}
    
    virtual void enable(){}
    virtual void disable(){}
    virtual void destroy(){}
};

struct Context{
        
};

void init_game(){
    
}
