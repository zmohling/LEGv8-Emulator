#include "parser.h"

#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "debug.h"
#include "instruction_impl.h"

const struct instruction_map opcode_map[] = {
    {OPCODE_ADD, format_R, ADDD}, {OPCODE_ADDI, format_I, ADDDI},
    {OPCODE_AND, format_R},       {OPCODE_ANDI, format_I},
    {OPCODE_B, format_B},         {OPCODE_B_COND, format_CB},
    {OPCODE_BL, format_B},        {OPCODE_BR, format_R},
    {OPCODE_CBNZ, format_CB},     {OPCODE_CBZ, format_CB},
    {OPCODE_DUMP, format_R},      {OPCODE_EOR, format_R},
    {OPCODE_EORI, format_I},      {OPCODE_HALT, format_R},
    {OPCODE_LDUR, format_D},      {OPCODE_LDURB, format_D},
    {OPCODE_LDURH, format_D},     {OPCODE_LDURSW, format_D},
    {OPCODE_LSL, format_R},       {OPCODE_LSR, format_R},
    {OPCODE_MUL, format_R},       {OPCODE_ORR, format_R},
    {OPCODE_ORRI, format_I},      {OPCODE_PRNL, format_R},
    {OPCODE_PRNT, format_R},      {OPCODE_SDIV, format_R},
    {OPCODE_SMULH, format_R},     {OPCODE_STUR, format_D},
    {OPCODE_STURB, format_D},     {OPCODE_STURH, format_D},
    {OPCODE_STURW, format_D},     {OPCODE_SUB, format_R},
    {OPCODE_SUBI, format_I},      {OPCODE_SUBIS, format_I},
    {OPCODE_SUBS, format_R},      {OPCODE_UDIV, format_R},
    {OPCODE_UMULH, format_R}};

static const uint32_t opcode_size_format_map[] = {0, 11, 10, 11, 6, 8, 9};

static opcode_tree_t* create_opcode_tree() {
  opcode_tree_t* tree = malloc(1 * sizeof(opcode_tree_t));

  tree->root = malloc(1 * sizeof(node_t));
  tree->root->left = NULL;
  tree->root->right = NULL;
  tree->root->instruction_func = NULL;

  for (int i = 0; i < NUM_OPCODES; i++) {
    instruction_format_t format = opcode_map[i].format;

    node_t* n = tree->root;

    for (int j = 0; j < opcode_size_format_map[format]; j++) {
      if (n == NULL) break;

      uint32_t val = (((opcode_map[i].opcode << j) & INT_MIN) == 0) ? 0 : 1;

      if (((n->left == NULL) && (val == 0)) ||
          ((n->right == NULL) && (val != 0))) {
        node_t* new_node = malloc(1 * sizeof(node_t));
        new_node->data = val;
        new_node->left = NULL;
        new_node->right = NULL;

        if (j == (opcode_size_format_map[format] - 1)) {
          new_node->instruction_func = opcode_map[i].instruction_func;
        } else {
          new_node->instruction_func = NULL;
        }

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

static void free_opcode_tree_rec(node_t* head) {
  if (head != NULL && head->left != NULL) free(head->left);
  if (head != NULL && head->right != NULL) free(head->right);
  if (head != NULL) free(head);
}

static void free_opcode_tree(opcode_tree_t* tree) {
  free_opcode_tree_rec(tree->root);
  free(tree);
}

instruction_t parse(uint32_t* word) {
  instruction_t instruction;
  instruction.word = *word;

  opcode_tree_t* tree = create_opcode_tree();
  node_t* n = tree->root;

  for (int i = 0; n != NULL; i++) {
    if (n->instruction_func) {
      instruction.instruction_func = n->instruction_func;
      break;
    }

    uint32_t val = (((instruction.word << i) & INT_MIN) == 0) ? 0 : 1;

    if (val == 0)
      n = n->left;
    else
      n = n->right;
  }

  free_opcode_tree(tree);

  return instruction;
}
