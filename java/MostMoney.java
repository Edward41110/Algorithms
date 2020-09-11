package myAlgorithms;

import java.util.Comparator;
import java.util.PriorityQueue;

public class MostMoney {
	
	public static class Project{
		int cost;
		int profit;
		public Project(int c, int p) {
			this.cost = c;
			this.profit = p;
		}
	}
	
	public static class CostComparator implements Comparator<Project>{
		@Override
		public int compare(Project p1, Project p2) {
			return p1.cost - p2.cost;
		}
	}
	
	public static class ProfitComparator implements Comparator<Project>{
		@Override
		public int compare(Project p1, Project p2) {
			return p2.profit - p1.profit;
		}
	}
	
	public static int mostMoney(int[]cost, int[]profit, int money, int k) {
		PriorityQueue<Project> costMin = new PriorityQueue<Project>(new CostComparator());
		PriorityQueue<Project> profitMax = new PriorityQueue<Project>(new ProfitComparator());
		for (int i = 0;i < cost.length;i++) {
			costMin.add(new Project(cost[i], profit[i]));
		}
		while ((!costMin.isEmpty()) && money >= costMin.peek().cost) {
			profitMax.add(costMin.poll());
		}
		for (int i = 0;i < cost.length && (!profitMax.isEmpty());i++) {
			money += profitMax.poll().profit;
			while ((!costMin.isEmpty()) && money >= costMin.peek().cost) {
				profitMax.add(costMin.poll());
			}
		}
		return money;
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[]cost = {5, 10, 6, 16};
		int[]profit = {3, 2, 4, 9};
		System.out.println(mostMoney(cost, profit, 7, 4));
	}

}
