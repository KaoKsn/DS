#include "vm.h"

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
      return;
    }
    vm->objects = get_stack(8);
    if (vm->objects == NULL) {
        free(vm);
        fprintf(stderr, "Failed to initialize an object frame!\n");
        return;
    }
    return vm;
}

void free_vm(vm_t *vm)
{
    if (vm == NULL) {
        return;
    }
    // Free both the frames and objects stack.
    free_stack(vm->frames);
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
    vm_frame_push(vm, frame);
    return frame;
}

void vm_push_frame(vm_t *vm, frame_t *frame)
{
    if (vm == NULL || frame == NULL) {
      return;
    }
    push(vm->frames, (void *)frame);
    return;
}

void free_frame(frame_t *frame)
{
    if (frame == NULL) {
        return;
    }
    stack_free(frame->references);
    free(frame);
}

void vm_track_object(vm_t *vm, object_t *obj)
{
  if (vm == NULL || obj == NULL){
    return;
  }
  push(vm->objects, (void*)obj);
  return;
}
