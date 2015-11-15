using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace GameOfLife
{
    public sealed class GOLGridControl : Control
    {
        public const int CELL_WIDTH = 10;
        private ILifeGrid _grid;


        public GOLGridControl()
        {
            BackColor = Color.White;
        }

        public GOLGridControl(ILifeGrid grid)
            : this()
        {
            Grid = grid;
        }

        protected override void OnClick(EventArgs e)
        {
            base.OnClick(e);
            if (null != Grid && e.GetType().Equals(typeof(MouseEventArgs)))
            {
                MouseEventArgs me = (MouseEventArgs)e;
                int x = me.X / CELL_WIDTH, y = me.Y / CELL_WIDTH;
                /*
                 * change the state of the cell (x,y)
                 */
                if (_grid[x, y].IsAlive)
                {
                    _grid[x, y].IsAlive = false;
                }
                else
                {
                    _grid[x, y].IsAlive = true;
                }
                _grid[x, y].OnChangeWrapper();
            }
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            if (null == Grid)
                return;
            for (int i = 0; i < Grid.Width; i++)
                for (int j = 0; j < Grid.Height; j++)
                    PaintCell(e.Graphics, i, j);
        }

        private void PaintCell(Graphics g, int x, int y)
        {
            g.FillRectangle(new SolidBrush(Grid[x, y].IsAlive ? Color.Black : Color.White), x * CELL_WIDTH, y * CELL_WIDTH, CELL_WIDTH, CELL_WIDTH);
        }


        //
        public void PaintOnChangeDelegate(ILifeCell cell)
        {
            Graphics graphics = CreateGraphics();

            PaintCell(graphics, cell.X, cell.Y);
        }

        public ILifeGrid Grid
        {
            get
            {
                return _grid;
            }
            set
            {
                _grid = value;
                if (null != value)
                {
                    Height = value.Height * CELL_WIDTH;
                    Width = value.Width * CELL_WIDTH;
                    /*
                     * register a delegate to the OnChange event of the cell (x,y) that paints the cell according to its state
					 * use CreateGraphics method to create the Graphics object of the control
                     */
                    for (int i = 0; i < value.Height; i++)
                    {
                        for (int j = 0; j < value.Width; j++)
                        {
                            _grid[i, j].OnChange += new LifeCellEventHandler(PaintOnChangeDelegate);
                        }
                    }

                    Refresh();
                }
            }
        }
    }
}
