

void morrisTraversal(node* root) {
  node* curr = root;
  while (curr != NULL) {
    if(curr->left == NULL) {
      visited(curr)
      curr = curr->next;
    }
    else {
      predecessor = find(sum)
      if(predecessor->right == NULL) {
        predecessor->right = curr;
        curr = curr->next;
      }
      else {
        predecessor->right = NULL;
        visited(curr);
        curr = curr->right;
      }
    }
  }
  
}