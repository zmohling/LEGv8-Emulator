#include "parser.h"

#include <stdint.h>
#include <stdlib.h>

#include "instruction_impl.h"

/* Struct to map opcode its format type and function implementation. */
const struct instruction_map opcode_map[] = {
    {OPCODE_ADD, format_R, ADD},    {OPCODE_ADDI, format_I, ADDI},
    {OPCODE_AND, format_R, AND},    {OPCODE_ANDI, format_I, ANDI},
    {OPCODE_B, format_B, B},        {OPCODE_B_COND, format_CB, B_COND},
    {OPCODE_BL, format_B, BL},      {OPCODE_BR, format_R, BR},
    {OPCODE_CBNZ, format_CB, CBNZ}, {OPCODE_CBZ, format_CB, CBZ},
    {OPCODE_DUMP, format_R, DUMP},  {OPCODE_EOR, format_R, EOR},
    {OPCODE_EORI, format_I, EORI},  {OPCODE_HALT, format_R, HALT},
    {OPCODE_LDUR, format_D, LDUR},  {OPCODE_LDURB, format_D},
    {OPCODE_LDURH, format_D},       {OPCODE_LDURSW, format_D},
    {OPCODE_LSL, format_R, LSL},    {OPCODE_LSR, format_R, LSR},
    {OPCODE_MUL, format_R, MUL},    {OPCODE_ORR, format_R, ORR},
    {OPCODE_ORRI, format_I, ORRI},  {OPCODE_PRNL, format_R, PRNL},
    {OPCODE_PRNT, format_R, PRNT},  {OPCODE_SDIV, format_R},
    {OPCODE_SMULH, format_R},       {OPCODE_STUR, format_D, STUR},
    {OPCODE_STURB, format_D},       {OPCODE_STURH, format_D},
    {OPCODE_STURW, format_D},       {OPCODE_SUB, format_R, SUB},
    {OPCODE_SUBI, format_I, SUBI},  {OPCODE_SUBIS, format_I, SUBIS},
    {OPCODE_SUBS, format_R, SUBS},  {OPCODE_UDIV, format_R, UDIV},
    {OPCODE_UMULH, format_R}};

/* Mapping of format type to its opcode size */
static const uint32_t opcode_size_format_map[] = {0, 11, 10, 11, 6, 8, 9};

static node_t* create_new_node() {
  node_t* n = malloc(1 * sizeof(node_t));

  n->left = NULL;
  n->right = NULL;
  n->instruction_func = NULL;

  return n;
}

/* Initalizes a tree-like data structure where each bit of an instruction's
 * opcode in a node. A node can have at most two children, left and right, or 0
 * and 1, respectively. */
static opcode_tree_t* create_opcode_tree() {
  opcode_tree_t* tree = malloc(1 * sizeof(opcode_tree_t));

  /* Initialize trival root node */
  tree->root = create_new_node();

  for (int i = 0; i < NUM_OPCODES; i++) {
    instruction_format_t format = opcode_map[i].format;

    node_t* n = tree->root;

    /* Iterate through the implemented instruction's opcodes and insert each
     * subsequent bit (MSB->LSB) into the tree. */
    for (int j = 0; j < opcode_size_format_map[format]; j++) {
      if (n == NULL) break;

      /* Bitwise AND operation on the MSB. If nonzero, the respective bit was a
       * 1, otherwise it was a 0. */
      uint32_t val = (((opcode_map[i].opcode << j) & (1 << 31)) == 0) ? 0 : 1;

      /* Create new node if not exists */
      if (((n->left == NULL) && (val == 0)) ||
          ((n->right == NULL) && (val != 0))) {
        node_t* new_node = create_new_node();

        /* Since no opcode can be a prefix of another, every leaf node signifies
         * the last bit of some opcode. These leaf nodes must be assigned a
         * pointer to the function which implements its functionality. */
        if (j == (opcode_size_format_map[format] - 1)) {
          new_node->instruction_func = opcode_map[i].instruction_func;
        }

        /* Update pointers to new node */
        if (val == 0) {
          n->left = new_node;
        } else {
          n->right = new_node;
        }
      }

      n = (val == 0) ? n->left : n->right;
    }
  }
  return tree;
}

/*
static void free_opcode_tree_rec(node_t* head) {
  if (head != NULL && head->left != NULL) free_opcode_tree_rec(head->left);
  if (head != NULL && head->right != NULL) free_opcode_tree_rec(head->right);
  if (head != NULL) free(head);
}

static void free_opcode_tree(opcode_tree_t* tree) {
  free_opcode_tree_rec(tree->root);
  free(tree);
}
*/

instruction_t parse(uint32_t* word) {
  static opcode_tree_t* tree;
  if (tree == NULL) tree = create_opcode_tree();

  instruction_t instruction;
  instruction.word = *word;

  node_t* n = tree->root;

  /* Traverse the tree until we match our opcode */
  for (int i = 0; n != NULL; i++) {
    if (n->instruction_func) {
      instruction.instruction_func = n->instruction_func;
      break;
    }

    uint32_t val = (((instruction.word << i) & (1 << 31)) == 0) ? 0 : 1;

    if (val == 0)
      n = n->left;
    else
      n = n->right;
  }

  /* Get format */
  for (int i = 0; i < NUM_OPCODES; i++) {
    if (opcode_map[i].instruction_func == instruction.instruction_func) {
      instruction.format = opcode_map[i].format;
      break;
    }
  }

  // free_opcode_tree(tree);

  return instruction;
}
