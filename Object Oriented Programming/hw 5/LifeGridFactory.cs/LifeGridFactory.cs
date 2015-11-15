using System;
using System.Collections.Generic;
using System.Text;

namespace GameOfLife {
    public static class LifeGridFactory {
        /// <summary>
        /// Generates an ILifeGrid grid of ILifeCell cells corresponding to the input grid.
        /// i.e. the IsAlive property of the (x,y) cell is grid[x,y].
        /// Each of the cells should be registered to the events of the grid and its neighbor cells on it.
        /// </summary>
        /// <param name="grid">A boolean bidimensional array corresponding corresponing to the state of
        /// the life grid.</param>
        /// <returns>A newly created ILifeGrid</returns>
        public static ILifeGrid CreateLifeGrid(bool[,] grid) 
        {

            int rowsNum     = grid.GetLength(0);
            int columnsNum  = grid.GetLength(1);

            LifeGrid newGrid = new LifeGrid(rowsNum, columnsNum);

            for(int i = 0; i < rowsNum; i++)
            {
            	for(int j = 0; j < columnsNum; j++)
            	{
                    newGrid[i, j].RegisterLifeGrid(newGrid);
                    newGrid[i, j].IsAlive = grid[i, j];
                    if (newGrid[i, j].IsAlive)
                    {
                        newGrid[i, j].OnChangeWrapper();
                    }
            	}
            }
            return newGrid;
        }

        /// <summary>
        /// Generates an ILifeGrid grid of ILifeCell cells of the given width and height.
        /// The IsAlive property of each of the cells should be set to false.
        /// Each of the cells should be registered to the events of the grid and its neighbor cells on it.
        /// </summary>
        /// <param name="width">The width (in cells) of the life grid</param>
        /// <param name="height">The height (in cells) of the life grid</param>
        /// <returns>A newly created ILifeGrid</returns>
        public static ILifeGrid CreateEmptyLifeGrid(int width, int height) 
        {
            LifeGrid newGrid = new LifeGrid(height, width);

            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    newGrid[i, j].RegisterLifeGrid(newGrid);
                    newGrid[i, j].IsAlive = false;
                    newGrid[i, j].NextGenerationIsAlive = newGrid[i, j].IsAlive;
                }
            }
            return newGrid;
        }
    }
}
