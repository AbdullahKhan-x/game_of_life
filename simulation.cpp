#include<vector>
#include<utility>
#include "simulation.hpp"

void Simulation::Draw()
{
    grid.Draw();
}

void Simulation::SetCellValue(int row, int column, int value)
{
    grid.SetValue(row, column, value);
}

int Simulation::CountLiveNeighbours(int row, int column)
{
    int liveNeighbours = 0;
    std::vector<std::pair<int, int>> neighbourOffsets =
    {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1},
        {-1, -1},
        {-1, 1},
        {1, -1},
        {1, 1}
    };

    for (const auto& offset : neighbourOffsets)
    {
        int neighbourRow = (row + offset.first + grid.GetRows()) % grid.GetRows();
        int neighbourColumn = (column + offset.second + grid.GetColumns()) % grid.GetColumns();
        liveNeighbours += grid.GetValue(neighbourRow, neighbourColumn);
    }
    return liveNeighbours;
}

void Simulation::Update()
{
    if (IsRunning())
    {
        for(int row = 0; row < grid.GetRows(); row++)
        {
            for (int column = 0; column < grid.GetColumns(); column++)
            {
                int liveNeighbours = CountLiveNeighbours(row, column);
                int cellValue = grid.GetValue(row, column);

                if (cellValue == 1)
                {
                    if (liveNeighbours > 3 || liveNeighbours < 2)
                    {
                        TempGrid.SetValue(row, column, 0);
                    }
                    else
                    {
                        TempGrid.SetValue(row, column, 1);
                    }
                }
                else
                {
                    if (liveNeighbours == 3)
                    {
                        TempGrid.SetValue(row, column, 1);
                    }
                    else
                    {
                        TempGrid.SetValue(row, column, 0);
                    }
                }
            }
        }
        grid = TempGrid;
    }
}

void Simulation::ClearGrid()
{
    if (!IsRunning())
    {
        grid.Clear();
    }
}

void Simulation::CreateRandomState()
{
    if (!IsRunning())
    {
        grid.FillRandom();
    }
}

void Simulation::ToggleCell(int row, int column)
{
    if(!IsRunning())
    {
        grid.ToggleCell(row, column);
    }
}
