#pragma once

template<typename T>
struct Array{
    T *data;
    int count;
    int max_count;

    Array(int max_amount){
        max_count = max_amount;
        count = 0;
        data = (T*)malloc(max_amount * sizeof(T));
    }
    
    T get(int index){
        return data[index];
    }
    
    T* get_ptr(int index){
        return &data[index];
    }
    
    void add(T value){
        if (count >= max_count) return;
        // T* element = get(count);
        // memmove(element, value, sizeof(T));
        data[count] = value;
        count++;
    }
    
    void remove(int index){
        for (int i = index; i < count - 1; i++){
            T *current_element = get(i);
            T *next_element = get(i + 1);
            memmove(current_element, next_element, size);
        }
        
        count--;
    }
    
    ~Array(){
        free(data);   
    }
};

char* to_string(int num){
    char* text = (char*)malloc(10 * sizeof(char));
    sprintf(text, "%d", num);
    return text;
}

char* to_string(f32 num){
    char* text = (char*)malloc(10 * sizeof(char));
    sprintf(text, "%f", num);
    return text;
}
char* to_string(f64 num){
    char* text = (char*)malloc(30 * sizeof(char));
    sprintf(text, "%f", num);
    return text;
}

const char* to_string(Color color){
    return TextFormat("{%d, %d, %d, %d}", color.r, color.g, color.b, color.a);
}

struct Old_Arr{  
    u8 *data;
    size_t size;
    int count;
    int max_count;
};

Old_Arr array_init(size_t size, int count = 10){
    Old_Arr array = {};
    array.size = size;
    array.data = (u8 *)malloc(count * size);
    array.max_count = count;
    
    return array;
}

void array_free(Old_Arr *array){
    free(array->data);
}

u8 *array_get(Old_Arr *array, int index){
    return (array->data) + index * array->size;
}

void array_add(Old_Arr *array, void *value){
    if (array->count >= array->max_count) return;
    u8* element = array_get(array, array->count);
    memmove(element, value, array->size);
    array->count++;
}

void array_remove(Old_Arr *array, int index){
    for (int i = index; i < array->count - 1; i++){
        u8 *current_element = array_get(array, i);
        u8 *next_element = array_get(array, i + 1);
        memmove(current_element, next_element, array->size);
    }
    
    array->count--;
}
