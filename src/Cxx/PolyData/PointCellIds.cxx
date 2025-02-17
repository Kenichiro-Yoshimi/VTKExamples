#include <vtkCellData.h>
#include <vtkIdFilter.h>
#include <vtkIdTypeArray.h>
#include <vtkPointData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkVersion.h>

int main(int, char*[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  std::cout << "There are " << sphereSource->GetOutput()->GetNumberOfPoints()
            << " points." << std::endl;
  std::cout << "There are " << sphereSource->GetOutput()->GetNumberOfCells()
            << " cells." << std::endl;

  vtkSmartPointer<vtkIdFilter> idFilter = vtkSmartPointer<vtkIdFilter>::New();
  idFilter->SetInputConnection(sphereSource->GetOutputPort());
#if VTK_MAJOR_VERSION > 8 || VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION >= 90
  idFilter->SetPointIdsArrayName("ids");
  idFilter->SetCellIdsArrayName("ids");
#else
  idFilter->SetIdsArrayName("ids");
#endif
  idFilter->Update();

  std::cout << "point arrays: " << std::endl;
  for (vtkIdType i = 0;
       i < idFilter->GetOutput()->GetPointData()->GetNumberOfArrays(); i++)
  {
    std::cout << idFilter->GetOutput()->GetPointData()->GetArrayName(i)
              << std::endl;
  }

  std::cout << "cell arrays: " << std::endl;
  for (vtkIdType i = 0;
       i < idFilter->GetOutput()->GetCellData()->GetNumberOfArrays(); i++)
  {
    std::cout << idFilter->GetOutput()->GetCellData()->GetArrayName(i)
              << std::endl;
  }

  vtkIdTypeArray* pointIds = vtkIdTypeArray::SafeDownCast(
      idFilter->GetOutput()->GetPointData()->GetArray("ids"));
  std::cout << "There are " << pointIds->GetNumberOfTuples() << " point ids"
            << std::endl;

  vtkIdTypeArray* cellIds = vtkIdTypeArray::SafeDownCast(
      idFilter->GetOutput()->GetCellData()->GetArray("ids"));
  std::cout << "There are " << cellIds->GetNumberOfTuples() << " cell ids"
            << std::endl;

  return EXIT_SUCCESS;
}
