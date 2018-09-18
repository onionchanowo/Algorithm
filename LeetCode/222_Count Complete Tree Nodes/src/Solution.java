public class Solution {

    public class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;
        TreeNode(int x) { val = x; }
    }

    private int dfs(TreeNode node){

        if(node == null){
            return 0;
        }

        int leftLeft = leftHeight(node.left);
        int leftRight = rightHeight(node.left);

        if(leftLeft == leftRight){
            return 1 + ((1 << leftLeft) - 1) + dfs(node.right);
        }

        return 1 + dfs(node.left) + ((1 << leftRight) - 1);
    }

    private int leftHeight(TreeNode node){

        if(node == null)
            return 0;

        return 1 + leftHeight(node.left);
    }

    private int rightHeight(TreeNode node){

        if(node == null)
            return 0;

        return 1 + rightHeight(node.right);
    }

    public int countNodes(TreeNode root) {

        if(root == null) return 0;

        return dfs(root);
    }
}