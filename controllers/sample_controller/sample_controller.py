# Copyright 1996-2024 Cyberbotics Ltd.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""
An example of a supervisor controller.
"""

import math

from controller import Supervisor


class Controller(Supervisor):
    SPEED = 6
    timeStep = 64

    def __init__(self):
        super(Controller, self).__init__()

    def run(self):
        self.root_node = self.getRoot()
        root_children_field = self.root_node.getField('children')
        n = root_children_field.getCount()
        print(f'This world contains {n} nodes:')
        # check what type of nodes are present in the world
        for i in range(n):
            node = root_children_field.getMFNode(i)
            print(f'-> {node.getTypeName()}')
        print()

        # get the content of the 'gravity' field of the 'WorldInfo' node
        node = root_children_field.getMFNode(0)
        field = node.getField('gravity')
        gravity = field.getSFFloat()
        print(f'WorldInfo.gravity = {gravity}\n')

controller = Controller()
controller.run()
