for (j = 0; j < remainingNodes; j++)
      {
          insertBST(root, &arrayOfnodes[i+j]);
          printf("node remaining %d\n", arrayOfnodes[i+j].value);
      }