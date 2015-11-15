using System;
using System.Collections.Generic;
using System.Text;

namespace GameOfLife
{
    public class LifeCell : ILifeCell
    {
        public event LifeCellEventHandler OnChange;
      
        private bool nextGenerationIsAlive;
        public bool NextGenerationIsAlive
        {
            get { return nextGenerationIsAlive;  }
            set { nextGenerationIsAlive = value; }
        }
        public void OnChangeWrapper()
        {
            this.OnChange(this);

        }

        //isAlive
        private bool isAlive;
        public bool IsAlive
        {
            get { return isAlive; }
            set { isAlive = value; }
        }

        //x
        private int x;
        public int X
        {
            get { return x; }
            set { x = value; }
        }

        //y
        private int y;
        public int Y
        {
            get { return y; }
            set { y = value; }
        }


        //neighborsAliveNum
        private int neighborsAliveNum;
        public int NeighborsAliveNum
        {
            get { return neighborsAliveNum; }
            set { neighborsAliveNum = value; }
        }


        //updateAliveNeighboursNum
        public void updateAliveNeighboursNum(ILifeCell cell)
        {
            if (cell.IsAlive)
            {
                this.NeighborsAliveNum++;
            }
            else
            {
                this.neighborsAliveNum--;
            }
        }


        //cellStatusInNextGeneration
        public void cellStatusInNextGeneration()
        {
            if (this.isAlive)
            {
                if (this.neighborsAliveNum < 2 || this.neighborsAliveNum > 3)
                {
                    this.nextGenerationIsAlive = false;
                }
                else
                {
                    this.nextGenerationIsAlive = true;
                }
            }
            else
            {
                if (this.neighborsAliveNum == 3)
                {
                    this.nextGenerationIsAlive = true;
                }
                else
                {
                    this.nextGenerationIsAlive = false;
                }
            }

            //TODO: ?
            //this.NeighborsAliveNum = 0;
        }


        //calculateNewGeneration: for the OnNewGeneration event
        public void calculateNewGeneration()
        {
            if (this.isAlive == this.nextGenerationIsAlive)
            {
                return;
            }
            else
            {
                this.isAlive = this.nextGenerationIsAlive;
                this.OnChange(this);
            }
        }


        //RegisterLifeGrid
        public void RegisterLifeGrid(ILifeGrid grid)
        {
            int i, j;

            for (i = Y - 1; i <= Y + 1; i++)
            {
                for (j = X - 1; j <= X + 1; j++)
                {
                    if (i != -1 && i != grid.Width && j != grid.Height && j != -1 && !(i == Y && j == X))
                    //if (i != -1 && j != grid.Width && i != grid.Height && j != -1 && !(j == X && i == Y))
                    {
                        this.OnChange += new LifeCellEventHandler(grid[j, i].updateAliveNeighboursNum);
                    }
                }
            }

            grid.OnPersistState += new LifeGridEventHandler(this.cellStatusInNextGeneration);

            grid.OnNewGeneration += new LifeGridEventHandler(this.calculateNewGeneration);
        }

        public LifeCell()
        {
            this.NeighborsAliveNum = 0;
        }
    }
}
