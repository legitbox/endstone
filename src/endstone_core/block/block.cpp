// Copyright (c) 2024, The Endstone Project. (https://endstone.dev) All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "endstone/detail/block/block.h"

#include "bedrock/world/level/dimension/dimension.h"
#include "endstone/detail/block/block_face.h"

namespace endstone::detail {
EndstoneBlock::EndstoneBlock(BlockSource &block_source, BlockPos block_pos)
    : block_source_(block_source), block_pos_(block_pos)
{
}

std::string EndstoneBlock::getType() const
{
    return block_source_.getBlock(block_pos_).getLegacyBlock().getFullNameId();
}

std::unique_ptr<Block> EndstoneBlock::getRelative(int offset_x, int offset_y, int offset_z)
{
    return getDimension().getBlockAt(getX() + offset_x, getY() + offset_y, getZ() + offset_z);
}

std::unique_ptr<Block> EndstoneBlock::getRelative(BlockFace face)
{
    return getRelative(face, 1);
}

std::unique_ptr<Block> EndstoneBlock::getRelative(BlockFace face, int distance)
{
    return getRelative(EndstoneBlockFace::getOffsetX(face) * distance, EndstoneBlockFace::getOffsetY(face) * distance,
                       EndstoneBlockFace::getOffsetZ(face) * distance);
}

Dimension &EndstoneBlock::getDimension() const
{
    return block_source_.getDimension().getEndstoneDimension();
}

int EndstoneBlock::getX() const
{
    return block_pos_.x;
}

int EndstoneBlock::getY() const
{
    return block_pos_.y;
}

int EndstoneBlock::getZ() const
{
    return block_pos_.z;
}

Location EndstoneBlock::getLocation() const
{
    return {&getDimension(), getX(), getY(), getZ()};
}

std::unique_ptr<EndstoneBlock> EndstoneBlock::at(BlockSource &block_source, BlockPos block_pos)
{
    return std::make_unique<EndstoneBlock>(block_source, block_pos);
}

}  // namespace endstone::detail
