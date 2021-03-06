registerNpc(315, {
  walk_speed        = 100,
  run_speed         = 250,
  scale             = 100,
  r_weapon          = 0,
  l_weapon          = 0,
  level             = 1,
  hp                = 94,
  attack            = 20,
  hit               = 70,
  def               = 500,
  res               = 500,
  avoid             = 500,
  attack_spd        = 10,
  is_magic_damage   = 0,
  ai_type           = 91,
  give_exp          = 4,
  drop_type         = 8,
  drop_money        = 1,
  drop_item         = 1,
  union_number      = 1,
  need_summon_count = 0,
  sell_tab0         = 0,
  sell_tab1         = 0,
  sell_tab2         = 0,
  sell_tab3         = 0,
  can_target        = 1,
  attack_range      = 100,
  npc_type          = 1,
  hit_material_type = 1,
  face_icon         = 0,
  summon_mob_type   = 0,
  quest_type        = 0,
  height            = 0
});

function OnInit(entity)
  return true
end

function OnCreate(entity)
  return true
end

function OnDelete(entity)
  return true
end

function OnDead(entity)
end

function OnDamaged(entity)
end