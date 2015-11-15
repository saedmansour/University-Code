using System;
using System.Collections.Generic;
using System.Text;

namespace GameOfLife
{
    public class LifeGrid : ILifeGrid
    {
        private LifeCell[,] grid;

        public event LifeGridEventHandler OnNewGeneration;
        public event LifeGridEventHandler OnPersistState;

        //Indexer
        public ILifeCell this[int x, int y]
        {
            get { return grid[x, y]; }
            //set { grid[x, y] = value; }
        }

        //width
        private int width;
        public int Width
        {
            get { return width; }
        }

        //height
        private int height;
        public int Height
        {
            get { return height; }
        }

        //delayInMiliseconds
        private int delayInMiliseconds;
        public int DelayInMiliseconds
        {
            get { return delayInMiliseconds; }
            set { delayInMiliseconds = value; }
        }

        //TODO:
        //Constructor
        public LifeGrid(int rowsNum, int columnNum)
        {
            grid = new LifeCell[rowsNum, columnNum];
            width = columnNum;
            height = rowsNum;

            for(int i = 0; i < rowsNum; i++)
            {
            	for(int j = 0; j < columnNum; j++)
            	{
                    grid[i, j]      = new LifeCell();
                    grid[i, j].X    = i;
                    grid[i, j].Y    = j;
            	}
            }
        }
        //run
        public void Run(int generations)
        {


            for (int i = 0; i < generations; i++)
            {
                this.OnPersistState();
                this.OnNewGeneration();
                System.Threading.Thread.Sleep(this.DelayInMiliseconds);
            }
        }
    }
}
