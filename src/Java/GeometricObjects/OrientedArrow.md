### Description

This example illustrates how to create and display an arrow that passes through two points.

It demonstrates two different ways to apply the transform:

1) Use vtkTransformPolyDataFilter to create a new transformed polydata. This method is useful if the transformed polydata is needed later in the pipeline, e.g. vtkGlyph3DFilter.
2) Apply the transform directly to the actor using vtkProp3D's SetUserMatrix. No new data is produced.
