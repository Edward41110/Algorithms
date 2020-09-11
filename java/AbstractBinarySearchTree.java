package myAlgorithms;

public class AbstractBinarySearchTree {
    static class Node{
        int value;
        Node parent;
        Node left;
        Node right;
        public Node(int element, Node parent, Node left, Node right) {
            this.value = element;
            this.parent = parent;
            this.left = left;
            this.right = right;
        }
    }

    public Node root;
    public int size;
    protected Node createNode(int element, Node parent, Node left, Node right) {
        return new Node(element, parent, left, right);
    }

    public Node search(int element) {
        Node node = root;
        while (node != null && node.value != element) {
            if (element < node.value) {
                node = node.left;
            } else {
                node = node.right;
            }
        }
        return node;
    }

    public Node insert(int element) {
        if (root == null) {
            root = createNode(element, null, null, null);
            size++;
            return root;
        }
        Node insertParentNode = null;
        Node searchTempNode = root;
        while (searchTempNode != null) {
            insertParentNode = searchTempNode;
            if (element < searchTempNode.value) {
                searchTempNode = searchTempNode.left;
            } else {
                searchTempNode = searchTempNode.right;
            }
        }
        Node newNode = createNode(element, insertParentNode, null, null);
        if (insertParentNode.value > newNode.value) {
            insertParentNode.left = newNode;
        } else {
            insertParentNode.right = newNode;
        }
        size++;
        return newNode;
    }

    public Node delete(int element) {
        Node deleteNode = search(element);
        if (deleteNode != null) {
            return delete(deleteNode);
        } else {
            return null;
        }
    }

    public Node delete(Node deleteNode) {
        if (deleteNode != null) {
            Node nodeToReturn;
            if (deleteNode.left == null) {
                nodeToReturn = transplant(deleteNode, deleteNode.right);
            } else if (deleteNode.right == null) {
                nodeToReturn = transplant(deleteNode, deleteNode.left);
            } else {
                Node successorNode = getMinimum(deleteNode.right);
                if (successorNode.parent != deleteNode) {
                    transplant(successorNode, successorNode.right);
                    successorNode.right = deleteNode.right;
                    successorNode.right.parent = successorNode;
                }
                transplant(deleteNode, successorNode);
                successorNode.left = deleteNode.left;
                successorNode.left.parent = successorNode;
                nodeToReturn = successorNode;
            }
            size--;
            return nodeToReturn;
        }
        return null;
    }

    /**
     * put one node from tree (newNode) to the place of another(nodeToReplace).
     * @param nodeToReplace Node which is replaced by newNode and removed from tree.
     * @param newNode New node.
     * @return New replaced node.
     */
    private Node transplant(Node nodeToReplace, Node newNode) {
        if (nodeToReplace.parent == null) {
            this.root = newNode;
        } else if (nodeToReplace == nodeToReplace.parent.left) {
            nodeToReplace.parent.left = newNode;
        } else {
            nodeToReplace.parent.right = newNode;
        }
        if (newNode != null) {
            newNode.parent = nodeToReplace.parent;
        }
        return newNode;
    }

    public int getMaximum() {
        return getMaximum(root).value;
    }

    public int getMinimum() {
        return getMinimum(root).value;
    }

    private Node getMinimum(Node node) {
        while (node.left != null) {
            node = node.left;
        }
        return node;
    }

    private Node getMaximum(Node node) {
        while (node.right != null) {
            node = node.right;
        }
        return node;
    }

    protected Node getSuccessPre(Node node) {
        // if there is left branch, then successor is leftmost node of that
        if (node.left != null) {
            return getMaximum(node.left);
        } else {
            // otherwise it is a lowest ancestor
            // whose right child is also ancestor of node
            Node currentNode = node;
            Node parentNode = node.parent;
            while (parentNode != null && currentNode == parentNode.left) {
                // go up until we find parent that
                // currentNode is not in left subtree
                currentNode = parentNode;
                parentNode = parentNode.parent;
            }
            return parentNode;
        }
    }

    protected Node getSuccessor(Node node) {
        // if there is right branch, then successor is leftmost node of that
        if (node.right != null) {
            return getMinimum(node.right);
        } else {
            // otherwise it is a lowest ancestor
            // whose left child is also ancestor of node
            Node currentNode = node;
            Node parentNode = node.parent;
            while (parentNode != null && currentNode == parentNode.right) {
                // go up until we find parent that
                // currentNode is not in right subtree
                currentNode = parentNode;
                parentNode = parentNode.parent;
            }
            return parentNode;
        }
    }
}
