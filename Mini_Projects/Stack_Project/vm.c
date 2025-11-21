#include "vm.h"
#include <stdio.h>

vm_t *create_vm()
{
    vm_t *vm = malloc(sizeof(vm_t));
    if (vm == NULL) {
        fprintf(stderr, "Mem Allocation for VM Failed!\n");
        return NULL;
    }
    // Create initialize the frames and objects stack.
    vm->frames = get_stack(8);
    if (vm->frames == NULL) {
        free(vm);
        fprintf(stderr, "Failed to initialize a stack frame!\n");
      return NULL;
    }
    vm->objects = get_stack(8);
    if (vm->objects == NULL) {
        free(vm);
        fprintf(stderr, "Failed to initialize an object frame!\n");
        return NULL;
    }
    return vm;
}

void free_vm(vm_t *vm)
{
    if (vm == NULL) {
        return;
    }
    // Free all the frames in the VM.
    for (int i = 0; i < vm->frames->top; i++) {
        // Free every frame.
        free_frame(vm->frames->data[i]);
    }
    free_stack(vm->frames);
    // Free all the objects associated to the VM.
    for (int i = 0; i < vm->objects->top; i++) {
        free_obj(vm->objects->data[i]);
    }
    free_stack(vm->objects);
    free(vm);
}

// Create a frame, and push it to the frames stack in VM.
frame_t *get_frame(vm_t *vm)
{
    if (vm == NULL) {
        fprintf(stderr, "VM = NULL!\n");
        return NULL;
    }
    frame_t *frame = malloc(sizeof(frame_t));
    if (frame == NULL) {
        fprintf(stderr, "Failed creating a frame!\n");
        return NULL;
    }
    frame->references = get_stack(8);
    if (frame->references == NULL) {
        free(frame);
        fprintf(stderr, "Failed creating references for the frame!\n");
        return NULL;
    }
    vm_push_frame(vm, frame);
    return frame;
}

// A wrapper function to push the frame into the VM after its creation.
void vm_push_frame(vm_t *vm, frame_t *frame)
{
    if (vm == NULL || frame == NULL) {
      return;
    }
    push(vm->frames, (void *)frame);
    return;
}

// Free a particular frame.
void free_frame(frame_t *frame)
{
    if (frame == NULL) {
        return;
    }
    // Free frame->references->data.
    // Objects not freed.
    free_stack(frame->references);
    free(frame);
}

// Push an object to the objects stack of the VM.
void vm_track_object(vm_t *vm, object_t *obj)
{
    if (vm == NULL || obj == NULL){
        return;
    }
    push(vm->objects, (void*)obj);
    return;
}

// Push an object into the frame.
void frame_reference_obj(frame_t *frame, object_t *obj)
{
    if (frame == NULL || obj == NULL) {
        return;
    }
    push(frame->references, (void *)obj);
}

// Iterate over each frame and set is_marked=true for every object that is referenced.
void mark(vm_t *vm)
{
    if (vm == NULL) {
        return;
    }
    // vm->frames <==> Stack of frames.
    // vm->frames->data[i] <==> A frame(stack of references).
    // vm->frames->data[i]->references->data[i] <==> object in the frame.
    for (int i = 0; i < vm->frames->top; i++) {
        // NOTE: A frame is pushed as void*
        frame_t *frame = vm->frames->data[i];
        for (int j = 0; j < frame->references->top; j++) {
            object_t *obj = frame->references->data[j];
            obj->is_marked = true;
        }
    }
}
