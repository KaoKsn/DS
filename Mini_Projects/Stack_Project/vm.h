// A VM is a container that has stack of frames and stack of objects.
typedef struct VM {
    stack_t *frames;
    stack_t *objects;
} vm_t;

// A frame is a stack of references.
typedef struct Frame {
    stack_t *references;
} frame_t;

vm_t *create_vm();
void free_vm(vm_t *vm);
// A wrapper function to push only frames into the vm.
// Avoid direct pushing into the frames stack.
void vm_push_frame(vm_t *vm, frame_t *frame);
frame_t *get_frame(vm_t *vm);
void free_frame(frame_t *frame);

void vm_track_object(vm_t *vm, object_t *obj);

